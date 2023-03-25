/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Msg.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:11:36 by rteles            #+#    #+#             */
/*   Updated: 2023/03/25 19:36:07 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_HPP
# define MSG_HPP

#define BOT_HELLO(botname, nickname) std::string("[" + botname + "] " + "Hello, "+nickname+"!")
#define	BOT_HELP(botname) std::string("[" + botname + "]\n" + "\
------------ SYSTEM ------------\n\
/nick [login]       change your login\n\
join [channel]     join channel\n\
leave              leave current channel\n\
quit               quit irc\n\
who                list of users in channel\n\
msg [login] [msg]  submit msg at login\n\
list               list of channel\n\
me                 defined an action\n\
\033[33m------------- BOT -------------\n\
!help		       	show help list\n\
\033[33m!game		       play a game \"Guess a Number")

#define	BOT_GAME(botname) std::string("[" + botname + "] " + "\
Let's PLAY A GAME!\n\
Guess the number I'm thinking of from 1 to 10!\n\
You have 10 seconds to guess!")
#define BOT_GAME_RESULT(botname,number) std::string("[" + botname + "] " + "The Number is: " + number)


#define BOT_LEAVE(botname) std::string("[" + botname + "] " + "BYE BYE!")

#define BOT_EXISTING(botname) std::string("[" + botname + "] " + "*Existing*")

#endif