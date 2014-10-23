/**
 Socket.cpp

 Copyright 2014 Gaston Martinez Gaston.martinez.90@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses
 */

#include "Socket.h"
#include <string>

#include <arpa/inet.h>

using std::string;

int _socket::get_port() {
	return this->_port;
}

void _socket::shutdown_socket() {
	shutdown(this->sockfd, SHUT_RDWR);
}

void _socket::close_port() {
	this->shutdown_socket();
	close(this->sockfd);
	this->sockfd = -1;
}

bool _socket::is_valid() {
	return (this->sockfd != -1);
}

Socket::Socket(int sockfd, sockaddr_in_s address) {
	this->sockfd = sockfd;
	this->_address = address;
}

Socket::Socket(int port, const string& host) {
	struct hostent *he;
	sockaddr_in_s address; 	// información de la dirección de destino
	he = gethostbyname(host.c_str());

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1)
		return; //TODO: LOGUEAR error

	address.sin_family = AF_INET;

	address.sin_port = htons(port); // short, Ordenación de bytes de la red
	address.sin_addr = *((struct in_addr *) he->h_addr);

	memset(&(address.sin_zero), '\0', 8); // poner a cero el resto de la

	int yes = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	int res = connect(sockfd, (struct sockaddr *) &address,
			sizeof(struct sockaddr));

	if (res == -1)
		return; //TODO: LOGUEAR error

	this->_port = port;
}

Socket::Socket() {
	this->sockfd = -1;
}

int Socket::send_message(const char* message, size_t message_len) {
	int res = send(sockfd, message, message_len, 0);
	if (res == -1)
		return res; //TODO: LOGUEAR error
	return res;
}

int Socket::receive(char* buff, size_t bytes_to_read) {
	ssize_t numbytes = recv(sockfd, buff, bytes_to_read, 0);

	if (numbytes <= 0)
		return numbytes; //TODO: LOGUEAR error

	return numbytes;
}

SocketQueue::SocketQueue() {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		return; //TODO: LOGUEAR error
}

void SocketQueue::init(int port, in_addr_t address) {
	sockaddr_in_s cli_addr;
	int cli_len = sizeof(cli_addr);

	cli_addr.sin_family = AF_INET;       //internet
	cli_addr.sin_addr.s_addr = address; //ip
	cli_addr.sin_port = htons(port);   //puerto

	memset(&(cli_addr.sin_zero), 0, sizeof(cli_addr.sin_zero));

	int yes = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	int res = bind(sockfd, (const struct sockaddr*) &cli_addr, cli_len);

	if (res == -1)
		return; //TODO: Loguear error

	this->_port = port;
}

void SocketQueue::init(int puerto, const char* direccion) {
	in_addr_t addr = inet_addr(direccion);
	this->init(puerto, addr);
}

Socket SocketQueue::accept_connection() {
	sockaddr_in_s their_addr;
	unsigned int sin_size = sizeof(struct sockaddr_in);
	int client = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);

	//if (client == -1) TODO: manejar el error y loguearlo

	return Socket(client, their_addr);
}

void SocketQueue::listen_connection(int backlog) {
	listen(sockfd, backlog);
}
