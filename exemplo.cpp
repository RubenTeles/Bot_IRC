/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemplo.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:59:36 by rteles            #+#    #+#             */
/*   Updated: 2023/03/23 16:00:58 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

using namespace std;

const int BUFFER_SIZE = 1024;
const char* SERVER_ADDRESS = "irc.freenode.net";
const int SERVER_PORT = 6667;
const char* CHANNEL_NAME = "#meu_canal";
const char* BOT_NAME = "meu_bot";
const char* BOT_PASSWORD = "senha_do_bot";

int main() {
    // Cria o socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Erro ao criar o socket" << endl;
        return 1;
    }

    // Conecta ao servidor
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDRESS, &serverAddr.sin_addr);
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Erro ao conectar ao servidor" << endl;
        return 1;
    }

    // Envia informações de login
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "NICK %s\r\nUSER %s 0 * :%s\r\n", BOT_NAME, BOT_NAME, BOT_NAME);
    send(sock, buffer, strlen(buffer), 0);
    snprintf(buffer, BUFFER_SIZE, "JOIN %s %s\r\n", CHANNEL_NAME, BOT_PASSWORD);
    send(sock, buffer, strlen(buffer), 0);

    // Cria a estrutura de eventos para o poll
    pollfd pollEvents[1];
    pollEvents[0].fd = sock;
    pollEvents[0].events = POLLIN;

    while (true) {
        // Espera por eventos de entrada/saída
        if (poll(pollEvents, 1, -1) < 0) {
            cerr << "Erro ao esperar por eventos" << endl;
            return 1;
        }

        // Verifica se há dados para ler no socket
        if (pollEvents[0].revents & POLLIN) {
            int bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (bytes < 0) {
                cerr << "Erro ao receber dados" << endl;
                return 1;
            }
            buffer[bytes] = '\0';
    
            // Verifica se o servidor está pedindo o ping
            if (strncmp(buffer, "PING", 4) == 0) {
                // Responde com o pong
                buffer[1] = 'O';
                send(sock, buffer, strlen(buffer), 0);
            }
    
            // Verifica se alguém mandou mensagem no canal
            char* pos = strstr(buffer, "PRIVMSG");
            if (pos != NULL) {
                // Separa o nome do usuário e a mensagem
                pos += 8;
                char* user = strtok(pos, "!");
                char* message = strtok(NULL, "\r\n");
    
                // Verifica se a mensagem começa com "bot"
                if (strncmp(message, "bot", 3) == 0) {
                    // Responde com uma mensagem
                    snprintf(buffer, BUFFER_SIZE, "PRIVMSG %s :Olá, %s! Como posso ajudar?\r\n", CHANNEL_NAME, user);
                    send(sock, buffer, strlen(buffer), 0);
                }
            }
        }
    }

    // Fecha o socket
    close(sock);

    return 0;
}