package main

import (
	"context"
	"io"
	"log"
	"os"
	"path/filepath"
	"sync"
	"time"

	media "Producerconsumer/proto"

	"google.golang.org/grpc"
)

const (
	videoFolder = "./videos"
	chunkSize   = 1024 * 64              // 64 KB
	delay       = 200 * time.Millisecond // Streaming speed
	numWorkers  = 3                      // Worker count || thread count
)

type VideoJob struct {
	Path     string
	Filename string
}

func main() {
	conn, err := grpc.Dial("consumer:50051", grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Failed to connect to consumer: %v", err)
	}
	defer conn.Close()

	/*
		Create a client || Setup through docker-compose || consumer is dependent on producer
	*/
	client := media.NewMediaUploadClient(conn)

	files, err := os.ReadDir(videoFolder)
	if err != nil {
		log.Fatalf("Failed to read videos folder: %v", err)
	}

	// Create a channel for the queue
	videoQueue := make(chan VideoJob, len(files))

	// Enqueue all videos
	for _, file := range files {
		if file.IsDir() {
			continue
		}
		videoQueue <- VideoJob{
			Path:     filepath.Join(videoFolder, file.Name()),
			Filename: file.Name(),
		}
	}
	close(videoQueue)

	/*
		Initializing semaphore-like variable for the goroutines/threads
	*/
	var wg sync.WaitGroup

	/*
		Checks how many goroutines will be made || it is equivalent to the amount of video files present in ./videos
	*/
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go func(workerID int) {
			defer wg.Done()
			for job := range videoQueue {
				log.Printf("[Worker %d] Streaming %s", workerID, job.Filename)
				if err := streamVideo(client, job.Path, job.Filename); err != nil {
					log.Printf("[Worker %d] Error streaming %s: %v", workerID, job.Filename, err)
				}
			}
		}(i + 1)
	}

	wg.Wait()
	log.Println("All videos streamed successfully")
}

// Goroutine || Go-equivalent of threads but lightweight || Separates each video into a single 'thread'
func streamVideo(client media.MediaUploadClient, filepath, filename string) error {
	f, err := os.Open(filepath)
	if err != nil {
		return err
	}
	defer f.Close()

	/*
		Sets up the streaming thread
	*/
	stream, err := client.UploadVideo(context.Background())
	if err != nil {
		return err
	}

	/*
		Gets a byte-chunk of the video
	*/
	buf := make([]byte, chunkSize)
	totalBytes := 0

	for {
		/*
			Just checks if video still has leftover bytes to send, else break
		*/
		n, err := f.Read(buf)
		if err == io.EOF {
			break
		}
		if err != nil {
			return err
		}

		totalBytes += n

		/*
			essentially, VideoChunk is a struct generated from media.proto using protoc
			typdef struct VideoChunk {
				string	Filename
				byte[]	Data
			}
		*/
		if err := stream.Send(&media.VideoChunk{
			Filename: filename,
			Data:     buf[:n],
		}); err != nil {
			return err
		}

		log.Printf("Streaming %s... %d bytes sent", filename, totalBytes)
		time.Sleep(delay) // Delay here
	}

	/*
		Close stream
	*/
	resp, err := stream.CloseAndRecv()
	if err != nil {
		return err
	}

	log.Printf("Upload complete for %s: %s", filename, resp.Message)
	return nil
}
