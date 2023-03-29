/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/29 18:10:54 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

std::string convertInput(int input)
{
	std::cout << "INPUT: " << input << std::endl;

	if (input == 1)
		return "rock";
	else if (input == 2)
		return "paper";
	else if (input == 3)
		return "scissor";
	else
		return "";
}

std::string	Bot::rockPapperScissors(std::string nick, std::string choise)
{
	std::string result = choise;
	int			input;
	std::srand(time(NULL));
	int random = 1 + (std::rand() % 3);
	
	if (choise != "rock" && choise != "paper" && choise != "scissor")
		return BOT_ERRO(nick, choise);

	if (choise == "rock")
		input = 1;
	else if (choise == "paper")
		input = 2;
	else if (choise == "scissor")
		input = 3;
	
	if (input == random)
	{
		setPlayer(nick, false, 50);
		result = BOT_DRAW(nick, "50") + " " + choise + " draw with a " + choise + "!";
	}
	else if (input - random == 1 || input - random == -2)
	{
		result = BOT_YOU_WIN(nick, "200") + " " + choise + " win a " + convertInput(random) + "!";
		setPlayer(nick, true, 200);
	}
	else
		result = BOT_YOU_LOSE(nick) + " " + choise + " lose for a " + convertInput(random) + "!";
		
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
	
	/*callBack = BOT_GAME();
	debug(message, callBack,user, channel);
		
	for (int i = 1; i < 10; i++)
		sleep(1);*/

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
	else
		result = BOT_YOU_LOSE(nick);

	return BOT_GAME_RESULT(convertToInt(random) + "\n" + result);
}

void Bot::game(std::string user, std::string channel, std::string message, std::string game, std::string choise)
{
	std::string callBack = "";

	addPlayer(user);
	if (game == "JanKenPo" || game == "jankenpo")
		callBack = rockPapperScissors(user, choise);
	else if (game == "GuessNumber" || game == "guessnumber")
		callBack = guessNumber(user, choise);

	if (!callBack.empty())
		debug(message, callBack, user, channel);
}