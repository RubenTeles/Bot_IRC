/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/30 00:48:50 by rteles           ###   ########.fr       */
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

std::string	Bot::rockPapperScissors(std::string nick, std::string choise)
{
	std::string result = choise;
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
		return BOT_ERRO(nick, choise);
	
	if (input == random)
	{
		setPlayer(nick, false, 50);
		result = BOT_DRAW(nick, "50") + " " + convertInput(input) + " draw with a " + convertInput(input) + "!";
	}
	else if (input - random == 1 || input - random == -2)
	{
		result = BOT_YOU_WIN(nick, "200") + " " + convertInput(input) + " win a " + convertInput(random) + "!";
		setPlayer(nick, true, 200);
	}
	else
		result = BOT_YOU_LOSE(nick) + " " + convertInput(input) + " lose for a " + convertInput(random) + "!";
		
	return result;
}
/*   WIN	     LOSE		 DRAW
	2-1 = 1		2-3 = -1	2-2 = 0
	3-2 = 1		3-1 = 2		3-3 = 0
	1-3 = -2	1-2 = -1	1-1 = 0
*/

std::string Bot::guessNumber(std::string nick, std::string choise)
{
	std::string result = "";
	std::srand(time(NULL));
	int random = (1 + (std::rand() % 10));
    std::istringstream iss(choise);
	int input;

	if (iss >> input)
		input = input;
	else
		return BOT_ERRO(nick, choise);

	if (input == random)
	{
		result = BOT_YOU_WIN(nick, "500");
		setPlayer(nick, true, 500);
	}
	else if (input > 10 || input < 1)
		return BOT_ERRO(nick, choise);
	else
		result = BOT_YOU_LOSE(nick);

	return result + " " + BOT_GAME_RESULT(convertToInt(random));
}

void Bot::game(std::string user, std::string channel, std::string message, std::string game, std::string choise)
{
	std::string callBack = "";
	(void)choise;
	addPlayer(user);
	if (game.find("JanKenPo") != std::string::npos)
		callBack = rockPapperScissors(user, game.substr(game.find("JanKenPo")+9, game.size()).c_str());
	else if (game.find("jankenpo") != std::string::npos)
		callBack = rockPapperScissors(user, game.substr(game.find("jankenpo")+9, game.size()).c_str());
	else if (game.find("GuessNumber") != std::string::npos)
		callBack = guessNumber(user, game.substr(game.find("GuessNumber")+11, game.size()).c_str());
	else if (game.find("guessnumber") != std::string::npos)
		callBack = guessNumber(user, game.substr(game.find("guessnumber")+11, game.size()).c_str());

	if (!callBack.empty())
		debug(message, callBack, user, channel);
}