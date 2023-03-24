/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/24 17:32:32 by rteles           ###   ########.fr       */
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
  	pollEvents[0].events = POLLIN | POLLHUP;	
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
	if (!_password.empty())
		sendMessage("PASS :", this->_password);
	else
		sendMessage("PASS ", this->_password);
	usleep(100);
	sendMessage("NICK ", this->_name);
	usleep(100);
	sendMessage("USER ", this->_name + " 0 * :" + this->_name);
	usleep(100);
	sendMessage("CAP ", "END");
}

void Bot::sendMessage(std::string const command, std::string const message)
{
	std::string	message_for_send = command + message + "\r\n";

	send(this->_socket, message_for_send.c_str(), message_for_send.size(), 0);
}

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
			std::cout << this->_name << " a Encerrar..." << std::endl;
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
			pollEvents[0].events = POLLIN | POLLHUP;
			pollEvents[0].revents = 0;
		}
		/*else if (!(pollEvents[0].revents & POLLOUT)) //mandou mensagem
			std::cout << i << " POLL: " << pollEvents[i].revents << "\n";  */      
	}
	sendMessage("QUIT :", BOT_LEAVE(_name));
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

/*
Prefixo: :alice!user@example.com
Comando: PRIVMSG
Parâmetro 1: #general
Parâmetro 2: Oi, como você está?
//Envio:

PRIVMSG #general :Oi, estou bem! E você?
		ou
PRIVMSG alice :Oi, estou bem! E você?
*/
void	Bot::privateMessage(std::string message)
{
/*
:alice!user@example.com PRIVMSG meu_bot :Hello, como você está?
:alice!user@example.com PRIVMSG meu_bot :!help
:alice!user@example.com PRIVMSG meu_bot :!game
:alice!user@example.com PRIVMSG #general meu_bot :!game
*/
	std::string		user = "";
	std::string		canal = "";
	std::string		command = "PRIVMSG ";
	std::string		callBack = "";
    std::size_t     found;
	char 			str[10];

	found = message.find(":");
	if (found != 0)
		return ;
	message = message.substr(1, message.size()).c_str();
	found = message.find(":");
	if (found == std::string::npos)
		return ;
	user = message.substr(0, message.find("!")).c_str();
	if (message.find("#") != std::string::npos)
	{
		canal = message.substr(message.find("#"), message.find(":")).c_str();
		canal = canal.substr(canal.find("#"), canal.find(" ")).c_str();
	}

	message = message.substr(message.find(":")+1, message.size()).c_str();

	callBack = message;

	std::cout << message << std::endl;
	if (message.find("Hello") != std::string::npos)
	{
		std::cout << "hello" << std::endl;
		callBack = BOT_HELLO(_name, user);
	}
	else if (message.find("!help") != std::string::npos ||
			message.find("!Help") != std::string::npos ||
			message.find("!HELP") != std::string::npos)
	{
		std::cout << "help" << std::endl;
		callBack = BOT_HELP(_name);
	}
	else if (message.find("!game") != std::string::npos ||
			message.find("!Game") != std::string::npos ||
			message.find("!GAME") != std::string::npos)
	{
		std::srand(time(NULL));
		int random = (1 + (std::rand() % 10));
		
		callBack = BOT_GAME(_name);
		sendMessage(command + user + " :", callBack);
		for (int i = 1; i < 10; i++)
			sleep(1);
		sprintf(str, "%d", random);
		callBack = "The Number is: ";
		callBack += str;
	}
	else
		callBack = "*Existing*";
	if (canal.empty())
		sendMessage(command + user + " :", callBack);
	else
		sendMessage(command + canal + " :", callBack);
}

void	Bot::response(std::string message)
{
	std::string		line;
    std::size_t     found;
	std::string		command = "";
	std::string		value;
	std::string		callBack = "";

	char str[10];

	if (message.find("PING") == 0)
	{
		value = message.substr(4, message.length()).c_str();
		callBack = "PONG" + value;
		sendMessage("", callBack);
	}
	else
	{
		found = message.find(" PRIVMSG ");
		if (found != std::string::npos)
			this->privateMessage(message);
		else
		{
			sprintf(str, "%ld", message.size());
			callBack = "Escreveste: \n" + message + " " + str;
			std::cout << "escreveste: " << message << std::endl;
			sendMessage("", callBack);
		}

		/*if (message.find("PRIVMSG") == 0)
		{
			found = message.find(":");
			command = message.substr(0, found).c_str();
			message = message.substr(found+1, found).c_str();
			if (message.find("!GAME"))
				sendMessage(command, );
			callBack = "Mandaste messagem privada maroto!";
		}*/
	}
}

/*

//Recebo:
:alice!user@example.com PRIVMSG meu_bot :Oi, como você está?

Prefixo: :alice!user@example.com
Comando: PRIVMSG
Parâmetro 1: #general
Parâmetro 2: Oi, como você está?

//Envio:

PRIVMSG #general :Oi, estou bem! E você?
		ou
PRIVMSG alice :Oi, estou bem! E você?

*/	