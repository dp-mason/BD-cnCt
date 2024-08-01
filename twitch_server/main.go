package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"
)

// func twitchWorker(chatUpdates chan string) {
// 	// or client := twitch.NewAnonymousClient() for an anonymous user (no write capabilities)
// 	client := twitch.NewClient("yourtwitchusername", "oauth:123123123")

// 	client.OnClearChatMessage(func(message twitch.ClearChatMessage) {
// 		fmt.Println(message.Message)
// 		chatUpdates <- message.Message
// 	})

// 	client.Join("dpmason")

// 	err := client.Connect()
// 	if err != nil {
// 		panic(err)
// 	}
// }

func fakeTwitchWorker(chatUpdates chan string) {
	for {
		time.Sleep(time.Second)
		chatUpdates <- "foobar"
		fmt.Println("fake twitch worker: foobar")
	}
}

type ChatUpdateResp struct {
	Message string `json:"message"`
	Status  int    `json:"status"`
}

func jsonServerWorker(chatUpdates chan string) {
	http.HandleFunc("/chat-queue", func(respWriter http.ResponseWriter, req *http.Request) {
		// construct the json string
		for msg := range chatUpdates {
			fmt.Println("JSON server:", msg)
		}

		// Create an instance of the response struct
		response := ChatUpdateResp{
			Message: "{Hello:git  World}",
			Status:  200,
		}

		respWriter.Header().Set("Content-Type", "application/json")

		// Encode the response struct to JSON
		jsonResponse, err := json.Marshal(response)
		if err != nil {
			// Handle the error and return an HTTP 500 status code
			http.Error(respWriter, err.Error(), http.StatusInternalServerError)
			return
		}

		respWriter.Write(jsonResponse)
	})

	fmt.Println("Server is running at 0.0.0.0:4554")
	log.Fatal(http.ListenAndServe("0.0.0.0:4554", nil))
}

func main() {
	chatUpdates := make(chan string, 16)
	//go twitchWorker(chatUpdates)
	go fakeTwitchWorker(chatUpdates)
	go jsonServerWorker(chatUpdates)

	select {}
}
