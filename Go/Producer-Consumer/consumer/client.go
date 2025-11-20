package main

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"os"
	"path/filepath"
	"sync"
	"time"

	media "Producerconsumer/proto"

	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

const (
	saveFolder = "./received_videos"
	httpPort   = 8080
	grpcPort   = 50051
	numWorkers = 3                     // Worker count || thread count
	flushDelay = 50 * time.Millisecond // For live playback
)

// Job queue structure based on already-existing gRPC
type videoChunkJob struct {
	filename string
	data     []byte
	done     bool // indicates write completion
}

// chan == channel
var jobQueue = make(chan videoChunkJob, 100)

// Server-sent events (SSE) clients for live notifications
var clientsMu sync.Mutex
var clients = make(map[chan string]bool)

// From generated gRPC code
type server struct {
	media.UnimplementedMediaUploadServer
	activeFiles sync.Map // filename → *os.File
}

func (s *server) UploadVideo(stream media.MediaUpload_UploadVideoServer) error {
	var filename string

	for {
		chunk, err := stream.Recv()
		if err == io.EOF {
			jobQueue <- videoChunkJob{filename: filename, done: true}
			return stream.SendAndClose(&media.UploadStatus{Message: "Upload completed"})
		}
		if err != nil {
			log.Printf("Error receiving chunk: %v", err)
			return err
		}

		if filename == "" {
			filename = chunk.Filename

			// Notify front-end immediately for live playback
			notifyNewVideo(filename)
		}

		jobQueue <- videoChunkJob{
			filename: filename,
			data:     chunk.Data,
			done:     false,
		}
	}
}

// Workers Goroutine for client, writes files in chunks from server
func startWorkers() {
	for i := 0; i < numWorkers; i++ {
		go func(workerID int) {
			for job := range jobQueue {
				fileInterface, _ := activeFile(job.filename)
				f := fileInterface.(*os.File)

				if !job.done {
					f.Write(job.data)
					f.Sync() // flush to disk so browser can start playing
					time.Sleep(flushDelay)
				} else {
					f.Close()
					log.Printf("[Worker %d] Finished writing %s\n", workerID, job.filename)
				}
			}
		}(i + 1)
	}
}

// Create or open file if not exists
var fileMap sync.Map

func activeFile(filename string) (interface{}, bool) {
	val, exists := fileMap.Load(filename)
	if exists {
		return val, true
	}

	os.MkdirAll(saveFolder, os.ModePerm)
	path := filepath.Join(saveFolder, filename)
	f, err := os.OpenFile(path, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		log.Fatalf("Failed opening file: %v", err)
	}

	fileMap.Store(filename, f)
	return f, false
}

// Notify all SSE clients about a new video
func notifyNewVideo(filename string) {
	clientsMu.Lock()
	defer clientsMu.Unlock()
	for ch := range clients {
		ch <- filename
	}
}

// SSE stream for live UI update
func sseEvents(w http.ResponseWriter, r *http.Request) {
	flusher, _ := w.(http.Flusher)

	ch := make(chan string)
	clientsMu.Lock()
	clients[ch] = true
	clientsMu.Unlock()
	defer func() {
		clientsMu.Lock()
		delete(clients, ch)
		clientsMu.Unlock()
	}()

	w.Header().Set("Content-Type", "text/event-stream")
	w.Header().Set("Cache-Control", "no-cache")

	for {
		select {
		case msg := <-ch:
			fmt.Fprintf(w, "data: %s\n\n", msg)
			flusher.Flush()
		case <-r.Context().Done():
			return
		}
	}
}

// JSON list of stored videos
func listVideos(w http.ResponseWriter, r *http.Request) {
	files, _ := os.ReadDir(saveFolder)
	list := []string{}
	for _, f := range files {
		if !f.IsDir() {
			list = append(list, f.Name())
		}
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(list)
}

// Runs at localhost:8080
// Serve individual videos directly at /video/<filename>
// No CSS for localhost:8080/video so only "links" will be visible
func startWebServer() {
	http.Handle("/", http.FileServer(http.Dir("web")))
	http.Handle("/video/", http.StripPrefix("/video/", http.FileServer(http.Dir(saveFolder))))
	http.HandleFunc("/events", sseEvents)
	http.HandleFunc("/videos-list", listVideos)

	log.Printf("HTTP server running at :%d", httpPort)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", httpPort), nil))
}

func main() {
	go startWorkers()
	go startWebServer()

	listener, err := net.Listen("tcp", fmt.Sprintf(":%d", grpcPort))
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	grpcServer := grpc.NewServer()
	media.RegisterMediaUploadServer(grpcServer, &server{})
	reflection.Register(grpcServer)

	log.Printf("gRPC server running at :%d with %d workers", grpcPort, numWorkers)
	log.Fatal(grpcServer.Serve(listener))
}
