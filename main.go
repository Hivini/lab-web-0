package main

import (
	"log"
	"net/http"
)

func main() {
	log.Println("Starting server...")
	http.Handle("/", http.FileServer(http.Dir("./html")))
	http.ListenAndServe("localhost:8080", nil)
}
