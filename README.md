# IRC bot in C++

This is an IRC bot written in C++ that offers several features such as games, leaderboard and user welcome. Users can interact with the bot using specific custom commands, making IRC chat more interactive and fun.

This project is a Bonus for [FT_IRC](https://github.com/zico15/ft_irc), this is an IRC Server.

## How it works
The bot is divided into several files, each responsible for a different part of the bot, such as connecting to the IRC server, interpreting commands, running games, maintaining the leaderboard and more.

Users can communicate with the bot using specific commands, such as `!help` to see available commands, or `!game jakenpo (option)` to play Rock, Paper, Scissors with the bot.

The bot can also welcome new users when they join the IRC chat channel and keep a leaderboard of users who have played games with it, showing who has the highest score.

## Features

* Welcoming new users: The bot can greet a user .
* Available commands: The bot has a help command (`!help`) that lists the available commands for users.
* Games: The bot has two games available: "JanKenPo" (Rock, Paper, Scissors) and "Guess a Number" (Guess a number from 1 to 10). Users can play these games with the bot using specific commands.
* Leaderboard: The bot maintains a leaderboard of users who played games with it, showing who has the highest score.
* Invites to other channels: Users can invite the bot to other IRC channels using the `!invite` command. The bot may require a password to join the channel, if specified.
