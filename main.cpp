/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 23:46:08 by rteles            #+#    #+#             */
/*   Updated: 2023/03/23 21:41:15 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int main(int argc, char **argv)
{
	try
	{
	    if (argc < 3)
		{
        	throw std::invalid_argument("Error: the bot don't have nothing to connect.");
			return (0);
		}

		Bot *b = new Bot(argv[1], argv[2], argc > 3 ? argv[3] : "", argc > 4 ? argv[4] : "Marvin");
		
		b->run();
		
		delete b;
	}
	catch(const std::exception& e) {
	    std::cerr << e.what() << std::endl;
	}

	return 0;
}

//./bot <host> <port> <password>
