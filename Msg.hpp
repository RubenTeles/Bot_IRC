/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Msg.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:11:36 by rteles            #+#    #+#             */
/*   Updated: 2023/03/25 01:51:26 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_HPP
# define MSG_HPP

#define BOT_HELLO(botname, nickname) std::string("\033[38;2;255;165;0m[" + botname + "] \033[0m" + "Hello, "+nickname+"!")
#define	BOT_HELP(botname) std::string("\033[38;2;255;165;0m[" + botname + "]\033[0m\n" + "\
\033[35m------------ SYSTEM ------------\n\
/nick [login]       \033[0mchange your login\n\
\033[35m/join [channel]     \033[0mjoin channel\n\
\033[35m/leave              \033[0mleave current channel\n\
\033[35m/quit               \033[0mquit irc\n\
\033[35m/who                \033[0mlist of users in channel\n\
\033[35m/msg [login] [msg]  \033[0msubmit msg at login\n\
\033[35m/list               \033[0mlist of channel\n\
\033[35m/me                 \033[0mdefined an action\n\
\033[33m------------- BOT -------------\n\
!help		       	\033[0mshow help list\n\
\033[33m!game		       \033[0mplay a game \"Guess a Number")

#define	BOT_GAME(botname) std::string("\033[38;2;255;165;0m[" + botname + "] \033[0m" + "\
Let's PLAY A GAME!\n\
Guess the number I'm thinking of from 1 to 10!\n\
You have 10 seconds to guess!")
#define BOT_GAME_RESULT(botname,number) std::string("\033[38;2;255;165;0m[" + botname + "] \033[0m" + "The Number is: " + number)


#define BOT_LEAVE(botname) std::string("\033[38;2;255;165;0m[" + botname + "] \033[0m" + "BYE BYE!")

#define BOT_EXISTING(botname) std::string("\033[38;2;255;165;0m[" + botname + "] \033[0m" + "*Existing*")

#endif