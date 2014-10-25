/**
 client_handler.h

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
#ifndef CLIENT_HANDLER_H_
#define CLIENT_HANDLER_H_

#include "../common/socket.h"
#include <string>


typedef char status_t;

class Client_handler {

private:
	bool _is_active;
	Socket _socket;

public:
	Client_handler(Socket& socket);
	virtual ~Client_handler();

public:
	static void execute_listen(Client_handler* handler);
	static void execute_send(Client_handler* handler);

private:
	void run_listen();

public:
	bool is_valid();
	bool is_active();
	void recicle();
	void stop();

	void send_message(std::string message);
};

#endif /* CLIENT_HANDLER_H_ */
