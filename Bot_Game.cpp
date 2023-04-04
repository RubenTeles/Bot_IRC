/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot_Game.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/04/03 01:31:29 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This code is a part of an IRC bot.
The first code snippet is the "addPlayer" function.
This function takes in a string and returns a map.
The code starts by checking if the map at the index of the given string is empty.
If it is not, the code will return the map.
If it is, the code will define a player variable and set it to an empty map.
The code will then set the EXP key in the player variable to 0, the WIN key in the player variable to 0, and the LEVEL key in the player variable to 1.
The code will then set the map at the index of the given string to the player variable.
The code will then return the map at the index of the given string.
The second code snippet is the "setPlayer" function.
This function takes in a string, a boolean, and an integer.
The code starts by checking if the given string is equal to the name of the bot.
If it is, the code will return.
If it is not, the code will define a player variable and set it to the result of the "addPlayer" function.
The code will then increment the EXP key of the player variable by the given integer.
The code will then increment the WIN key of the player variable by the given boolean.
The code will then check if the value of the EXP key of the player variable is greater than or equal to the value of the LEVEL key of the player variable multiplied by 100.
If the value of the EXP key of the player variable is greater than or equal to the value of the LEVEL key of the player variable multiplied by 100, the code will decrement the value of the EXP key of the player variable by the value of the LEVEL key of the player variable multiplied by 100.
The code will then increment the value of the LEVEL key of the player variable by 1.
The code will then set the map at the index of the given string to the player variable.
The third code snippet is the "showLeaderBoard" function.
This function returns a string.
The code starts by defining 2 iterator variables.
The code then defines a board variable and sets it to an empty vector.
The code will then define a leaderBoard variable and set it to "------ LEADER BOARD ------".
The code will then enter a for loop that will run for each map in the _players map.
The code will then check if the board vector contains the value of the LEVEL key of the current map multiplied by 100 plus the value of the EXP key of the current map.
If the board vector does not contain the value of the LEVEL key of the current map multiplied by 100 plus the value of the EXP key of the current map, the code will push the value of the LEVEL key of the current map multiplied by 100 plus the value of the EXP key of the current map to the board vector.
The code will then sort the board vector and reverse it.
The code will then enter another for loop that will run for each integer in the board vector.
The code will then enter another for loop that will run for each map in the _players map.
The code will then check if the current integer in the board vector is equal to the value of the LEVEL key of the current map multiplied by 100 plus the value of the EXP key of the current map.
If the current integer in the board vector is equal to the value of the LEVEL key of the current map multiplied by 100 plus the value of the EXP key of the current map, the code will print the position of the player, the name of the player, the level of the player, the EXP of the player, and the EXP needed to level up.
The code will then increment the position variable by 1.
The code will then return the leaderBoard variable.
The fourth code snippet is the "invite" function.
This function takes in a string.
The code starts by sending a message to the given string.
The fifth code snippet is the "welcomeChannel" function.
This function takes in a string.
The code starts by defining a channel variable.
The code will then check if the given string contains "#".
If it does not, the code will return.
If it does, the code will set the channel variable to the given string.
The code will then send a welcome message to the channel.
The sixth code snippet is the "trim" function.
This function takes in a string and returns a string.
The code starts by checking if the given string is empty.
If it is not, the code will return the given string.
If it is, the code will define a length variable and set it to the length of the given string minus 1.
The code will then enter a while loop that will run until the length variable is greater than or equal to 0 and the given string at the index of the length variable is a space.
The code will then decrement the length variable by 1.
The code will then return the given string from the start up to the value of the length variable plus 1.
*/
#include "Bot.hpp"

std::string convertInput(int input)
{
	if (input == 1)
		return "Rock";
	else if (input == 2)
		return "Paper";
	else if (input == 3)
		return "Scissor";
	else
		return "";
}

void	Bot::rockPapperScissors(std::string nick, std::string choise, Game *game)
{
	std::string result;
	int			input = 0;
	int random = game->getResult();
	
	if (choise.find("rock") != std::string::npos)
		input = 1;
	else if (choise.find("paper") != std::string::npos)
		input = 2;
	else if (choise.find("scissor") != std::string::npos)
		input = 3;
	else
		return ;
	
	game->setResult(random);
	
	if (input == random)
		game->setWinnerOrLosser(nick, 1);
	else if (input - random == 1 || input - random == -2)
		game->setWinnerOrLosser(nick, 2);
	else
		game->setWinnerOrLosser(nick, 0);
}
/*   WIN	     LOSE		 DRAW
	2-1 = 1		2-3 = -1	2-2 = 0
	3-2 = 1		3-1 = 2		3-3 = 0
	1-3 = -2	1-2 = -1	1-1 = 0
*/

void Bot::guessNumber(std::string nick, std::string choise, Game *game)
{
	std::string result = "";
	int random = game->getResult();
    std::istringstream iss(choise);
	int input;

	game->setResult(random);

	if (iss >> input)
		input = input;
	else
		return ;

	if (input == random)
		game->setWinnerOrLosser(nick, 2);
	else
		game->setWinnerOrLosser(nick, 0);
}

void Bot::gamePlay(std::string user, std::string channel, std::string message, std::string game)
{
	std::string callBack = "";
	Game		*room_game;

	addPlayer(user);
	if (game.find("jankenpo") != std::string::npos)
	{
		if (!channel.empty())
			room_game = addGame(channel, JANKENPO, 10, 200, 1 + (std::rand() % 3));
		else
			room_game = addGame(user, JANKENPO, 0, 200, 1 + (std::rand() % 3));
		
		rockPapperScissors(user, game.substr(game.find("jankenpo")+9, game.size()).c_str(), room_game);
		
		room_game->setVitory("You default a " + convertInput(room_game->getResult()) + "!");
	}
	else if (game.find("guess") != std::string::npos)
	{
		if (!channel.empty())
			room_game = addGame(channel, GUESS, 10, 1000, 1 + (std::rand() % 10));
		else
			room_game = addGame(user, GUESS, 0, 1000, 1 + (std::rand() % 10));

		guessNumber(user, game.substr(game.find("guess")+6, game.size()).c_str(), room_game);
		
		room_game->setVitory("The Number is: " + convertToString(room_game->getResult()));
	}

	(void)message;
}

Game	*Bot::addGame(std::string room, int game, int time, int reward, int result)
{
    if (!_games[room])
	{
		std::string gameMessage = "";
		_games[room] = new Game(room, game, time, reward, result);
		std::cout << "\033[35mNEW GAME ROOM: " << room << "\033[0m" << std::endl;
		if (game == GUESS)
			gameMessage = "Guess the Number! I'm thinking a number from 1 to 10! Using !game guess 1-10";
		else if (game == JANKENPO)
			gameMessage = "JanKenPo! Try too beat me! Using !game jankenpo rock/paper/scissors!";
		debug("", BOT_GAME(gameMessage, convertToString(_games[room]->getTimeLimit())), "", room);
	}

	return _games[room];
}

std::string	Bot::winners(std::string room)
{
	if (!_games[room])
		return "";

	std::string garbage = room;

	Game *game = _games[room];
	
	std::vector<std::string> winners = game->getWinners();
	std::vector<std::string> draws = game->getDraws();
	std::vector<std::string> losers = game->getLosers();
	std::vector<std::string>::iterator user;
	int reward = game->getReward();
	for (user = winners.begin(); user != winners.end(); ++user)
    {
		std::string callBack = BOT_YOU_WIN(*user, convertToString(reward)) + " " + game->getVictory();
		debug("", callBack, *user, "");
		setPlayer(*user, true, reward);
		usleep(100);
	}
	for (user = draws.begin(); user != draws.end(); ++user)
    {
		std::string callBack = BOT_DRAW(*user, convertToString(50));
		debug("", callBack, *user, "");
		setPlayer(*user, true, 50);
		usleep(100);
	}
	for (user = losers.begin(); user != losers.end(); ++user)
    {
		std::string callBack = BOT_YOU_LOSE(*user);
		debug("", callBack, *user, "");
		usleep(100);
	}

	if (game->getGame() == GUESS)
		debug("", BOT_GAME_RESULT(convertToString(game->getResult()), convertToString(winners.size())), "", room);
	else
		debug("", BOT_GAME_RESULT(convertInput(game->getResult()), convertToString(winners.size())), "", room);

	delete _games[room];

	std::cout << "\033[35mDELETE GAME ROOM: " << garbage << "\033[0m" << std::endl;

	return garbage;
}

void	Bot::gameTime(void)
{
    std::map<std::string, Game *>::iterator it;
	std::vector<std::string> finish_games;
	
	for (it = this->_games.begin(); it != this->_games.end(); ++it)
    {
		(*it).second->setTime(1);
		if ((*it).second->getTimeLimit() <= 0)
			finish_games.push_back(this->winners((*it).second->getRoom()));
	}

    std::vector<std::string>::iterator v_it;
	for (v_it = finish_games.begin(); v_it != finish_games.end(); ++v_it)
	{
		if (!(*v_it).empty())
			_games.erase(*v_it);
	}
}
