package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"strconv"
	"strings"
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
		time.Sleep(time.Millisecond * 200)
		var chatmsg string = "/0 2.5"
		fmt.Println("fake twitch worker: ", chatmsg)
		if chatmsg[0] == '/' {
			parts := strings.Split((chatmsg[1:]), " ")
			channel, err := strconv.Atoi(parts[0])
			if err != nil {
				continue
			}
			if channel < 0 || channel > 15 {
				// TODO: send error msg back thru twitch chat
				continue
			}
			value, err := strconv.ParseFloat(parts[1], 32)
			if err != nil {
				continue
			}
			if value < -10.0 || value > 10.0 {
				// TODO: send error msg back thru twitch chat
				continue
			}
			chatUpdates <- parts[0] + " " + parts[1]
		}
	}
}

func jsonServerWorker(chatUpdates chan string) {
	http.HandleFunc("/chat-queue", func(respWriter http.ResponseWriter, req *http.Request) {
		data := make(map[string]string)

		for {
			select {
			case msg := <-chatUpdates:
				fmt.Println("Flushed message: ", msg)
				cmdParts := strings.Split(msg, " ")
				data[cmdParts[0]] = cmdParts[1]
			default:
				// No more messages in the channel
				fmt.Println(data)
				// Convert the data structure to JSON
				jsonData, err := json.Marshal(data)
				if err != nil {
					http.Error(respWriter, err.Error(), http.StatusInternalServerError)
					return
				}

				// Set the content type to application/json
				respWriter.Header().Set("Content-Type", "application/json")

				// Write the JSON data to the response
				respWriter.Write(jsonData)
				return
			}
		}

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
