/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/23 18:28:28 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(void)
{
    std::cout << "Bot Default Constructor!" << std::endl;
}

Bot::Bot(std::string host, char * port, std::string password, std::string name) : 
_name(name), _hostname(host), _port(port), _password(password) 
{
    struct sockaddr_in   target;
    
    _socket = socket(AF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
		throw std::runtime_error("Error: While opening socket.");

	bzero((char *) &target, sizeof(target));

    target.sin_family = AF_INET;
    target.sin_port = htons(atof(port));
    target.sin_addr.s_addr = INADDR_ANY;

	int	host_connect = connect(_socket, (struct sockaddr *)&target, sizeof(target));
    if (host_connect < 0)
		throw std::runtime_error("Erro: Bot can't connect the Server!");
	
	std::cout << "Conectado!" << std::endl;
	
	this->pollEvents = new pollfd[1];

	pollEvents[0].fd = _socket;
  	pollEvents[0].events = POLLIN;	
	/*pollEvents[1].fd = host_connect;
  	pollEvents[1].events = POLLIN;*/
	//close(_socket);
	//close(host_connect);
}

Bot::Bot( Bot const & src)
{
    *this = src;
}

Bot::~Bot() {
	delete pollEvents;
    std::cout << "Bot Destructor!" << std::endl;
}

Bot & Bot::operator=(Bot const & rhs)
{
    if (this != &rhs)
    {
        //this->_type = rhs._type;
    }

    return *this;
}

void	Bot::authenticate(void)
{
	std::string login = "NICK " + this->_name + "\r\n" + "USER " + this->_name + " 0 * :" + this->_name;
	
	send(_socket, login.c_str(), login.size(), 0);
}
/*
void Bot::sendMessage(std::string const message)
{
	std::string	message_for_send = message + "\r\n";
	send(this->_socket, message.c_str(), message.size(), 0);
	
    //std::cout << "* use something in " << target.getName() << " *" << std::endl;
}*/

void Bot::run(void)
{
	this->authenticate();
    while (true)
    {
        if (poll(pollEvents, 1, -1) < 0) //poll
			throw std::runtime_error("Erro: Waiting for Events!");

        /*if (pollEvents[0].revents == 0)
		{
        	continue ;
		}*/
		if (pollEvents[0].revents & POLLHUP) //Quando encerra a conexao
		{
			std::cout << this->_name << "A Encerrar..." << std::endl;
        	break ;
		}
		/*if (pollEvents[0].fd == _socket)
		{
			std::cout << "soocket\n";
	        //execute(NULL, "connect");
		}
		else */
		if (pollEvents[0].revents & POLLIN) //recebeu um comando
		{
			std::cout << "recebeu" << std::endl;
			this->recive();
			pollEvents[0].events = POLLIN;
			pollEvents[0].revents = 0;
		}
		/*else if (!(pollEvents[0].revents & POLLOUT)) //mandou mensagem
			std::cout << i << " POLL: " << pollEvents[i].revents << "\n";  */      
	}

	close(_socket);
}

void	Bot::recive(void)
{
	int			size;
	char		buffer[BUFFER_SIZE];
	std::string message;
	
	size = recv(_socket, buffer, BUFFER_SIZE - 1, 0);
	while (size)
	{
		if (size < 0)
			throw std::runtime_error("Erro: Recive Dates!");
		buffer[size] = '\0';
		message += buffer;
		if (size != BUFFER_SIZE)
			break ;
		size = recv(_socket, buffer, BUFFER_SIZE - 1, 0);
	}

	if (message.empty())
		return ;

	this->response(message);
}

void	Bot::response(std::string message)
{
	std::string		line;
    std::size_t     found;
	std::string		value;
	std::string		callBack = "";

char str[10];


	if (message.find("PING") == 0 && message.size() == 5)
		callBack = "PONG";
	else
	{
		found = message.find("PRIVMSG");
		if (found == 0)
		{
			value = message.substr(8, message.length()).c_str();
			callBack = "Mandaste messagem privada maroto!";
		}
		else
		{
			sprintf(str, "%ld", message.size());
			callBack = "Escreveste: \n" + message + " " + str;
		}
	}
	
	send(this->_socket, callBack.c_str(), callBack.size(), 0);
}