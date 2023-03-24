/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Msg.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:11:36 by rteles            #+#    #+#             */
/*   Updated: 2023/03/24 17:30:15 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_HPP
# define MSG_HPP

#define BOT_HELLO(botname, nickname) std::string("[" + botname + "] " + "Hello, "+nickname+"!")
#define	BOT_HELP(botname) std::string("[" + botname + "]\n" + "\
/*------------ SYSTEM ------------\n\
/nick [login]       change your login\n\
/join [channel]     join channel\n\
/leave              leave current channel\n\
/quit               quit irc\n\
/who                list of users in channel\n\
/msg [login] [msg]  submit msg at login\n\
/list				list of channel\n\
/me                 defined an action\n\
[msg]               send msg in channel\n\
------------- BOT -------------\n\
!help		       	show help list\n\
!game		       	play a game \"Guess a Number")

#define	BOT_GAME(botname) std::string("[" + botname + "] " + "\
Let's PLAY A GAME!\n\
Guess the number I'm thinking of from 1 to 10!\n\
You have 10 seconds to guess!")

#define BOT_LEAVE(botname) std::string("[" + botname + "] " + "BYE BYE!")

#endif