/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:47 by rteles            #+#    #+#             */
/*   Updated: 2023/03/25 16:47:39 by rteles           ###   ########.fr       */
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
    
    _socket = socket(AF_INET, SOCK_STREAM, 0);//IPV 4, TCP

	if (_socket < 0)
		throw std::runtime_error("Error: While opening socket.");

	bzero((char *) &target, sizeof(target));

    target.sin_family = AF_INET;
    target.sin_port = htons(atof(port));
    target.sin_addr.s_addr = INADDR_ANY;

	int	host_connect = connect(_socket, (struct sockaddr *)&target, sizeof(target));
    if (host_connect < 0)
		throw std::runtime_error("Erro: Bot can't connect the Server!");
	
	this->pollEvents = new pollfd[1];

	pollEvents[0].fd = _socket;
  	pollEvents[0].events = POLLIN;
	//pollEvents[1].fd = host_connect;
  	//pollEvents[1].events = POLLIN;
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
        this->_name = rhs._name;
		this->_hostname = rhs._hostname;
		this->_port = rhs._port;
		this->_password = rhs._password;
		this->_socket = rhs._socket;
    }

    return *this;
}

void	Bot::authenticate(void)
{
	if (!_password.empty())
		sendMessage("PASS :", this->_password);
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
		{
			delete this;
			throw std::runtime_error("Erro: Waiting for Events!");
		}
		if (pollEvents[0].revents & POLLHUP) //Quando encerra a conexao
		{
			std::cout << this->_name << " a Encerrar..." << std::endl;
        	break ;
		}
		if (pollEvents[0].revents & POLLIN) //recebeu um comando
		{
			if (this->recive() == 1)
				break ;
			pollEvents[0].events = POLLIN;
			pollEvents[0].revents = 0;
		}
	
	}
	sendMessage("QUIT :", BOT_LEAVE(_name));
	close(_socket);
}

int	Bot::recive(void)
{
	int			size;
	char		buffer[BUFFER_SIZE];
	std::string message;
	
	size = recv(_socket, buffer, BUFFER_SIZE - 1, 0);
	while (size)
	{
		if (size < 0)
		{
			std::cerr << "Erro: Recive!" << std::endl;
			return 1;
		}
		buffer[size] = '\0';
		message += buffer;
		if (size != BUFFER_SIZE)
			break ;
		size = recv(_socket, buffer, BUFFER_SIZE - 1, 0);
	}

	if (message.empty())
		return 0;

	return this->response(message);
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
:alice!user@example.com PRIVMSG meu_bot :sad
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
	user = message.substr(0, message.find("!user")).c_str();
	if (message.find("#") != std::string::npos)
	{
		canal = message.substr(message.find("#"), message.find(":")).c_str();
		canal = canal.substr(canal.find("#"), canal.find(" ")).c_str();
	}

	callBack = message.substr(message.find(":")+1, message.size()).c_str();

	callBack = message;

	//	------ Message -------	
	//std::cout << message << std::endl;
	
	if (message.find("Hello") != std::string::npos)
		callBack = BOT_HELLO(_name, user);
	else if (message.find("!help") != std::string::npos ||
			message.find("!Help") != std::string::npos ||
			message.find("!HELP") != std::string::npos)
		callBack = BOT_HELP(_name);
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
		callBack = BOT_GAME_RESULT(_name, str);
	}
	else
		callBack = BOT_EXISTING(_name);

	std::cout << "\033[32m[" << user << "] \033[0m" << message;
	std::cout << callBack << std::endl;
	
	if (canal.empty())
		sendMessage(command + user + " :", callBack);
	else
		sendMessage(command + canal + " :", callBack);

}

int	Bot::response(std::string message)
{
	std::string		line;
    std::size_t     found;
	std::string		command = "";
	std::string		value;
	std::string		callBack = "";

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
			if (message.find(":Password incorrect") != std::string::npos && message.find("464") != std::string::npos)
			{
				std::cerr << "Erro: Password incorrect!" << std::endl;
				return 1;
			}
			if (message.find(":Nickname incorreta.") != std::string::npos && message.find("433") != std::string::npos)
			{
				std::cerr << "Erro: Nickname incorrect!" << std::endl;
				return 1;
			}
			if (message.find(":Welcome to server, "+this->_name) != std::string::npos && message.find("001") != std::string::npos)
			{
				std::cout << "\033[32mConnected!\033[0m" << std::endl;
				return 0;
			}
			std::cout << message << std::endl;
		}
	}
	return 0;
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

/*
    std::string user = "";
    int         send_fd = -1;
    std::string message = "PRIVMSG ";

    user = data.substr(0, data.find_first_of(SPACES, 0));
    
    if (user.empty())
        return ;
    
    message = "PRIVMSG " + user + " ";
    std::cout << "User: " << user << std::endl;
    std::cout << "message: " << message << std::endl;
    
	data = &data[user.size()];
	data = trim(data);
    std::cout << "data: " << data << std::endl;
*/