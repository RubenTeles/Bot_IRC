/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Msg.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:11:36 by rteles            #+#    #+#             */
/*   Updated: 2023/03/28 09:10:33 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_HPP
# define MSG_HPP

#define BOT_HELLO(nickname) std::string("Hello, "+nickname+"!")
#define	BOT_HELP() std::string("------------ SYSTEM ------------\n\
/nick [login]       change your login\n\
join [channel]     join channel\n\
leave              leave current channel\n\
quit               quit irc\n\
who                list of users in channel\n\
msg [login] [msg]  submit msg at login\n\
list               list of channel\n\
me                 defined an action\n\
------------- BOT -------------\n\
!help		       	show help list\n\
!game		       play a game \"Guess a Number")

#define	BOT_GAME() std::string("Let's PLAY A GAME! Guess the number I'm thinking of from 1 to 10! You have 10 seconds to guess!")

#define BOT_GAME_RESULT(number) std::string("The Number is: " + number)

#define BOT_LEAVE() std::string("BYE BYE!")

#endif