package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"strconv"
	"strings"

	"github.com/gempir/go-twitch-irc/v4"
	"github.com/joho/godotenv"
)

func twitchWorker(chatUpdates chan string) {
	// or client := twitch.NewAnonymousClient() for an anonymous user (no write capabilities)
	user := strings.TrimSpace(os.Getenv("TWITCH_USER"))
	key := strings.TrimSpace(os.Getenv("TWITCH_OAUTH"))
	client := twitch.NewClient(user, key)

	client.OnPrivateMessage(func(message twitch.PrivateMessage) {
		fmt.Println(message.Message)
		if message.Message[0] == '!' {
			parts := strings.Split((message.Message[1:]), " ")
			if len(parts) < 2 {
				// TODO: send error msg back thru twitch chat
				client.Reply(message.Channel, message.ID, "Send a message that follows the format ![0-15] [0.0-10.0]")
				return
			}

			channel, err := strconv.Atoi(parts[0])

			if err != nil {
				client.Reply(message.Channel, message.ID, "There was an issue parsing the channel of "+
					"your command, please enter an integer 0-15")
				return
			} else if channel < 0 || channel > 15 { // TODO: consolidate magic number
				client.Reply(message.Channel, message.ID, "Please enter a channel 0-15")
				return
			}

			value, err := strconv.ParseFloat(parts[1], 32)

			if err != nil {
				client.Reply(message.Channel, message.ID, "There was an issue parsing the value of "+
					"your command, please enter a number")
				return
			} else if value < 0.0 || value > 10.0 { // TODO: consolidate magic number
				client.Reply(message.Channel, message.ID, "Please enter a value between 0.0 and 10.0")
				return
			}

			// TODO: consolidate magic number
			if len(chatUpdates) == 16 {
				client.Reply(message.Channel, message.ID, "The command buffer is full, please wait for it to empty")
			}
			client.Reply(message.Channel, message.ID, "Your command will be apllied shortly")
			chatUpdates <- parts[0] + " " + parts[1]
		}
	})

	fmt.Println("Joining", user, "...")
	client.Join(user)

	err := client.Connect()
	if err != nil {
		panic(err)
	}
}

// func fakeTwitchWorker(chatUpdates chan string) {
// 	for {
// 		time.Sleep(time.Millisecond * 200)
// 		var chatmsg string = "/15 2.5"
// 		fmt.Println("fake twitch worker: ", chatmsg)
// 		if chatmsg[0] == '/' {
// 			parts := strings.Split((chatmsg[1:]), " ")
// 			channel, err := strconv.Atoi(parts[0])
// 			if err != nil {
// 				continue
// 			}
// 			if channel < 0 || channel > 15 {
// 				// TODO: send error msg back thru twitch chat
// 				continue
// 			}
// 			value, err := strconv.ParseFloat(parts[1], 32)
// 			if err != nil {
// 				continue
// 			}
// 			if value < -10.0 || value > 10.0 {
// 				// TODO: send error msg back thru twitch chat
// 				continue
// 			}
// 			chatUpdates <- parts[0] + " " + parts[1]
// 		}
// 	}
// }

func jsonServerWorker(chatUpdates chan string) {
	http.HandleFunc("/chat-queue", func(respWriter http.ResponseWriter, req *http.Request) {
		data := make(map[string]string)

		// loop until all messages have been flushed, then respond with the json data
		for {
			select {
			case msg := <-chatUpdates:
				fmt.Println("Flushed message: ", msg)
				cmdParts := strings.Split(msg, " ")
				data[cmdParts[0]] = cmdParts[1]
			default:
				// No more messages in the channel
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
	// loads the twitch user and oauth from .env file
	err := godotenv.Load(".env")
	if err != nil {
		panic(err)
	}
	chatUpdates := make(chan string, 16)
	go twitchWorker(chatUpdates)
	// go fakeTwitchWorker(chatUpdates)
	go jsonServerWorker(chatUpdates)

	select {}
}
