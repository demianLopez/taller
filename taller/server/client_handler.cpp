/**
 client_handler.cpp

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
#include "client_handler.h"

#include <iostream>
#include <thread>
#include <chrono>

Client_handler::Client_handler(Socket& socket) {
	this->_is_active = true;
	this->socket = socket;
}

Client_handler::~Client_handler() {
	this->socket.shutdown_socket();
	this->socket.close_port();
}

bool Client_handler::is_valid() {
	return this->socket.is_valid(); //TODO: agregar mas condiciones
}

bool Client_handler::is_active() {
	return this->_is_active;
}

void Client_handler::run() {
	//Threadear la escucha que es lo que pasa menos seguido
	while (this->is_active()) {
		//Send from socket
		std::cout << "Printing from thread: " << std::this_thread::get_id()
				<< std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	socket.shutdown_socket();
	socket.close_port();
}

void Client_handler::recicle() {
	std::cout << "Stop" << std::endl;
	this->socket.close_port();
}

void Client_handler::execute(Client_handler* handler) {
	handler->_is_active = true;
	handler->run();
}

void Client_handler::stop() {
	std::cout << "Stop" << std::endl;
	this->socket.shutdown_socket();
	this->_is_active = false;
}
