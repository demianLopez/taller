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

#include <stdio.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

Client_handler::Client_handler(Socket& socket) {
	this->_is_active = true;
	this->_socket = socket;
}

Client_handler::~Client_handler() {
	this->_socket.shutdown_socket();
	this->_socket.close_port();
}

bool Client_handler::is_valid() {
	return this->_socket.is_valid(); //TODO: agregar mas condiciones
}

bool Client_handler::is_active() {
	return this->_is_active;
}

void Client_handler::run_listen() {
	//Threadear la escucha que es lo que pasa menos seguido
	char message[100];
	message[10] = '\0';
	while (this->is_active()) {
		//Send from socket
		int bytes_read = this->_socket.receive(message, 10);

		if (bytes_read < 1) {
			std::cerr << "Error de conexion con el cliente. Desconexion"
					<< std::endl;
			break;
		}

		message[bytes_read] = '\0';

		std::string mess = std::string(message);

		std::cout << "El gil del thread -" << std::this_thread::get_id()
				<< "- dice:" << mess << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	_socket.shutdown_socket();
	_socket.close_port();
}

void Client_handler::recicle() {
	std::cout << "Stop" << std::endl;
	this->_socket.close_port();
}

void Client_handler::execute_listen(Client_handler* handler) {
	handler->_is_active = true;
	handler->run_listen();
}

void Client_handler::stop() {
	std::cout << "Stop" << std::endl;
	this->_socket.shutdown_socket();
	this->_is_active = false;
}

void Client_handler::send_message(message_command_t& message) {
	if (!_socket.is_valid()) return;

	size_t command_len = sizeof(command_id_type_t);
	size_t message_len = command_len;

	size_t command_len_len = sizeof(command_len_type_t);
	message_len += command_len_len;

	message_len += message.args_len;

	char* message_buffer = new char[message_len];

	memcpy (message_buffer,&message.command,command_len);
	memcpy (message_buffer+command_len,&message.args_len,command_len_len);
	memcpy (message_buffer+command_len+command_len_len,message.command_args,message.args_len);

	int sent = 0;

	while (sent<message_len){
		int bytes_sent = _socket.send_message(message_buffer+sent,message_len-sent);

		if (bytes_sent < 0){
			sent = bytes_sent;
			break;
		}

		sent += bytes_sent;
	}

	delete[] message_buffer;

	if (sent < 0){
		//handle error;
		return;
	}
}
