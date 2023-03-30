/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot_Game.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/30 03:36:31 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	std::srand(time(NULL));
	int random = 1 + (std::rand() % 3);
	
	if (choise.find("rock") != std::string::npos)
		input = 1;
	else if (choise.find("paper") != std::string::npos)
		input = 2;
	else if (choise.find("scissor") != std::string::npos)
		input = 3;
	else
		return ;
	
	if (input == random)
	{
		game->setWinnerOrLosser(nick, 1);
		/*setPlayer(nick, false, 50);
		result = BOT_DRAW(nick, "50") + " " + convertInput(input) + " draw with a " + convertInput(input) + "!";*/
	}
	else if (input - random == 1 || input - random == -2)
	{
		game->setWinnerOrLosser(nick, 2);
		/*result = BOT_YOU_WIN(nick, "200") + " " + convertInput(input) + " win a " + convertInput(random) + "!";
		setPlayer(nick, true, 200);*/
	}
	else
		game->setWinnerOrLosser(nick, 0);
		//result = BOT_YOU_LOSE(nick) + " " + convertInput(input) + " lose for a " + convertInput(random) + "!";
}
/*   WIN	     LOSE		 DRAW
	2-1 = 1		2-3 = -1	2-2 = 0
	3-2 = 1		3-1 = 2		3-3 = 0
	1-3 = -2	1-2 = -1	1-1 = 0
*/

void Bot::guessNumber(std::string nick, std::string choise, Game *game)
{
	std::string result = "";
	std::srand(time(NULL));
	int random = (1 + (std::rand() % 10));
    std::istringstream iss(choise);
	int input;

	if (iss >> input)
		input = input;
	else
		return ;

	if (input == random)
	{
		game->setWinnerOrLosser(nick, 2);
		/*result = BOT_YOU_WIN(nick, "500");
		setPlayer(nick, true, 500);*/
	}
	else
		game->setWinnerOrLosser(nick, 2);
		/*result = BOT_YOU_LOSE(nick);

		
	return result + " " + BOT_GAME_RESULT(convertToInt(random));*/
}

void Bot::gamePlay(std::string user, std::string channel, std::string message, std::string game)
{
	std::string callBack = "";
	Game		*room_game;

	addPlayer(user);
	if (game.find("jankenpo") != std::string::npos)
	{
		if (!channel.empty())
			room_game = addGame(channel, JANKENPO, 10, 1 + (std::rand() % 3), 200);
		else
			room_game = addGame(user, JANKENPO, 0, 1 + (std::rand() % 3), 200);

		room_game->setVitory("You default a " + convertInput(room_game->getResult()));
		
		rockPapperScissors(user, game.substr(game.find("jankenpo")+9, game.size()).c_str(), room_game);
	}
	else if (game.find("guessnumber") != std::string::npos)
	{
		if (!channel.empty())
			room_game = addGame(channel, GUESS, 10, 1 + (std::rand() % 10), 1000);
		else
			room_game = addGame(user, GUESS, 0, 1 + (std::rand() % 10), 1000);

		room_game->setVitory(BOT_GAME_RESULT(convertInput(room_game->getResult())));
		
		guessNumber(user, game.substr(game.find("guessnumber")+11, game.size()).c_str(), room_game);
	}
	(void)message;
}

Game	*Bot::addGame(std::string room, int game, int time, int result, int reward)
{
    if (!_games[room])
	{
		_games[room] = new Game(room, game, time, result, reward);
		std::cout << "NEW GAME ROOM: " << room << std::endl;
	}


	return _games[room];
}

void	Bot::winners(std::string room)
{
	if (!_games[room])
		return ;

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
		usleep(50);
	}
	for (user = draws.begin(); user != draws.end(); ++user)
    {
		std::string callBack = BOT_DRAW(*user, convertToString(50));
		debug("", callBack, *user, "");
		setPlayer(*user, true, 50);
		usleep(50);
	}
	for (user = losers.begin(); user != losers.end(); ++user)
    {
		std::string callBack = BOT_YOU_LOSE(*user);
		debug("", callBack, *user, "");
		usleep(50);
	}

	if (game->getGame() == GUESS)
		debug("", BOT_GAME_RESULT(convertToString(game->getResult())), "", room);

	delete _games[room];

	_games.erase(room);
}

void	Bot::gameTime(void)
{
    std::map<std::string, Game *>::iterator it;
	clock_t end = clock();
	
	for (it = this->_games.begin(); it != this->_games.end(); ++it)
    {
		std::cout << "START: " << (*it).second->getStartTime() << std::endl;
		std::cout << "END: " << end << std::endl;
		std::cout << "Time: " << (end - (*it).second->getStartTime()) / 100 << std::endl;
		if ((end - (*it).second->getStartTime()) / 100 >= (*it).second->getTimeLimit())
			this->winners((*it).second->getRoom());
	}
}