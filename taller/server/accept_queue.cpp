/**
 accept_queue.cpp

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
#include "accept_queue.h"

#define QUEUE_SIZE 20

Accept_queue::Accept_queue() {
	// TODO Auto-generated constructor stub

}

Accept_queue::~Accept_queue() {
	// TODO Auto-generated destructor stub
}

Client_handler* Accept_queue::accept_client() {
	Socket socket = this->queue.accept_connection();

	if(!socket.is_valid()){
		return NULL;
	}

	return new Client_handler(socket);
}

bool Accept_queue::is_open() {
	return this->queue.is_valid();
}

void Accept_queue::initialize(int port) {
	this->queue.init(port);
	if (!this->queue.is_valid())
		return;
	this->queue.listen_connection(QUEUE_SIZE);
}

void Accept_queue::close() {
	this->queue.shutdown_socket();
	this->queue.close_port();
}
