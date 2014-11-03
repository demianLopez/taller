/**
 socket.h

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
#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h>    //hostent
#include <string.h>   //memset
#include <unistd.h>   //close

#include <string>

//Definiciones para reducir codigo
typedef struct in_addr in_addr_s;
typedef struct sockaddr_in sockaddr_in_s;

class _socket {
protected:
	int sockfd; //File descriptor del socket
	int _port;  //Puerto asociado al socket
	sockaddr_in_s _address; //Direccion de conexion

protected:
	_socket() {
	}
	;

public:
	virtual void close_port();
	virtual void shutdown_socket();
	virtual int get_port();
	virtual bool is_valid();
};

class Socket: public _socket {

public:

	Socket(); //dummy
	Socket(int port, const std::string& host = "127.0.0.1");
	Socket(int sockfd, sockaddr_in_s direccion);

	int receive(char* buff, size_t bytes_to_read);
	int send_message(std::string message);
	int send_message(const char* message, size_t message_len);

};

class SocketQueue: public _socket {

private:
	bool binded = false;

public:
	/**
	 * Crea una nueva cola de socket no asociada a algun puerto
	 */
	SocketQueue();
	void init(int port, in_addr_t address = INADDR_ANY);
	void init(int port, const char* address);
	void listen_connection(int backlog = 20);
	bool is_valid();

	Socket * accept_connection();
};

#endif
