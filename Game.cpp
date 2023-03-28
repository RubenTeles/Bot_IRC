/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/28 18:06:29 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

std::string	Bot::rockPapperScissors(std::string nick, std::string choise)
{
	std::string result = "";
	int			input;
	std::srand(time(NULL));
	int random = (1 + (std::rand() % 3));
	
	if (choise == "rock")
		input = 1;
	else if (choise == "paper")
		input = 2;
	else if (choise == "scissor")
		input = 3;
	
	if (input == random)
		result = "It's a DRAW!";
	else if (input - random == 1 || input - random == -3)
		result = "You Win!";
	else
		result = "You Lose!";
	
	std::cout << result << std::endl;
	
	return result;
}
/*   WIN	     LOSE		 DRAW
	2-1 = 1		2-3 = -1	2-2 = 0
	3-2 = 1		3-1 = 2		3-3 = 0
	1-3 = -3	1-2 = -1	1-1 = 0
*/