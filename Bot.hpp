/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:44 by rteles            #+#    #+#             */
/*   Updated: 2023/03/28 09:03:05 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BOT_HPP
# define BOT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/poll.h>
#include <sstream>

#include <stdlib.h>
#include "Msg.hpp"

#define BUFFER_SIZE 1024

class Bot
{
    private:
        std::string _name;
        std::string _hostname;
		std::string	_port;
		std::string	_password;
        int			_socket;
		pollfd		*pollEvents;

        Bot(void);

    public:
		Bot(std::string host, char * port, std::string password, std::string name);
        Bot(std::string const & type);
        Bot( Bot const & src);
        
        ~Bot(void);

        Bot & operator=(Bot const & rhs);

        void    authenticate(void);
		void	run(void);
		int 	recive(void);
		int 	response(std::string message);
		void	sendMessage(std::string const command, std::string const message);
		void	privateMessage(std::string message);
        void    debug(std::string message, std::string callBack, std::string user, std::string channel);
        void    quit(void);

};

#endif