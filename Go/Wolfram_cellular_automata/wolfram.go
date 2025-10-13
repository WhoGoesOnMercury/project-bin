package main

import (
	"fmt"
	"net/http"
	"text/template"
)

func main() {
	fileserver := http.FileServer(http.Dir("static"))
	http.Handle("/static/", http.StripPrefix("/static/", fileserver))

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		template, err := template.ParseFiles("templates/wolfram.html")
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		template.Execute(w, nil)
	})

	fmt.Println("Server running at http://localhost:3000")
	http.ListenAndServe(":3000", nil)
}
