require('dotenv').config();
const TwitchJs = require('twitch-js').default;
const express = require('express');

// Set up express server
const app = express();
const PORT = 5309;

// Channel for Twitch updates
const chatUpdates = [];

// Twitch worker function
function twitchWorker() {
  const twitchUser = process.env.TWITCH_USER.trim();
  const twitchOauth = process.env.TWITCH_OAUTH.trim();

  const twitchClient = new TwitchJs({
    token: twitchOauth,
    username: twitchUser,
  });

  // Twitch private message handler
  twitchClient.on('PRIVMSG', (message) => {
    const msgText = message.message;

    if (msgText.startsWith('!')) {
      const parts = msgText.slice(1).split(' ');

      if (parts.length < 2) {
        twitchClient.say(message.channel, 'Send a message that follows the format ![0-15] [0.0-10.0]');
        return;
      }

      const channel = parseInt(parts[0], 10);
      const value = parseFloat(parts[1]);

      if (isNaN(channel) || channel < 0 || channel > 15) {
        twitchClient.say(message.channel, 'Please enter a channel 0-15');
        return;
      }

      if (isNaN(value) || value < 0.0 || value > 10.0) {
        twitchClient.say(message.channel, 'Please enter a value between 0.0 and 10.0');
        return;
      }

      if (chatUpdates.length === 16) {
        twitchClient.say(message.channel, 'The command buffer is full, please wait for it to empty');
      } else {
        twitchClient.say(message.channel, 'Your command will be applied shortly');
        chatUpdates.push(`${parts[0]} ${parts[1]}`);
      }
    }
  });

  twitchClient.on('JOIN', (message) => {
    twitchClient.say(message.channel, `WELCOME: ${message.username}`);
  });

  console.log(`Joining ${twitchUser}...`);
  twitchClient.join(twitchUser);

  twitchClient.connect();
}

// JSON server worker function
app.get('/twitch-queue', (req, res) => {
  const data = {};

  while (chatUpdates.length > 0) {
    const msg = chatUpdates.shift(); // Get the oldest message
    console.log('Flushed message: ', msg);
    const [channel, value] = msg.split(' ');
    data[channel] = value;
  }

  res.json(data);
});

app.listen(PORT, () => {
  console.log(`Server is running at 0.0.0.0:${PORT}`);
});

// Start the workers
twitchWorker();
