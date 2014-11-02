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
#include "DataObserver.h"

#include <stdio.h>

#include <iostream>

#include <chrono>
#include <string>

void Client_handler::threadFunction(Client_handler * client) {
	signal(SIGPIPE, SIG_IGN);
	while (client->isConnected()) {
		if (!client->runListen()) {
			client->stop();
		}
	}

}

void Client_handler::waitThreadEnd() {
	this->clientThread.join();
}

Client_handler::Client_handler(Socket& socket) {
	this->_socket = socket;
	this->threadLoop = true;
	this->dataObserver = NULL;
	this->clientThread = thread(Client_handler::threadFunction, this);
}

Client_handler::~Client_handler() {
	if (dataObserver != NULL) {
		delete dataObserver;
	}
}

bool Client_handler::is_valid() {
	return this->_socket.is_valid(); //TODO: agregar mas condiciones
}

void Client_handler::setDataObserver(DataObserver * dO) {
	this->dataObserver = dO;
}

bool Client_handler::runListen() {
	//Threadear la escucha que es lo que pasa menos seguido
	char message[256];

	//Send from socketa

	//char longMensaje[10];
	//int bytes_read = this->_socket.receive(longMensaje, 1);
	//std::cout<<longMensaje<<std::endl;

	int bytes_read = this->_socket.receive(message, 256);

	if (bytes_read < 0) {
		if (dataObserver != NULL) {
			dataObserver->errorConnection(this, bytes_read);
		} else {
			std::cout << "Error de conexion con el cliente. Desconexion"
					<< std::endl;
		}
		return false;
	}

	if (bytes_read == 0) {
		if (this->threadLoop) {
			if (dataObserver != NULL) {
				dataObserver->closeConnection(this);
			} else {
				std::cout << "Se perdio la conexion" << std::endl;
			}
		}
		return false;
	}

	if (bytes_read > 0) {
		message[bytes_read] = '\0';

		if (dataObserver != NULL) {
			Message * m = new Message(message, bytes_read);
			dataObserver->dataArribal(m, this);
			delete m;
		} else {

			std::string mess = std::string(message);

			std::cout << "El gil del thread -" << std::this_thread::get_id()
			<< "- dice:" << mess << std::endl;
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	return true;
}

bool Client_handler::isConnected() {
	return this->threadLoop;
}

void Client_handler::stop() {
	this->threadLoop = false;
	_socket.shutdown_socket();
	_socket.close_port();
}

bool Client_handler::send_message(Message * msg) {
	if (_socket.is_valid()) {
		int sent = -1;

		sent = _socket.send_message(msg->getMessageData(),
				msg->getMessageLength());

		if (sent < 1) {
			this->stop();
			return false;
		}

		return true;
	}
	return false;
}

bool Client_handler::send_message(const char * msg, int size) {
	if (_socket.is_valid()) {
		int sent = -1;

		sent = _socket.send_message(msg, size);

		if (sent < 1) {
			this->stop();
			return false;
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	return true;
}

void Client_handler::send_message(message_command_t& message) {
	if (!_socket.is_valid())
		return;

	size_t command_len = sizeof(command_id_type_t);
	size_t message_len = command_len;

	size_t command_len_len = sizeof(command_len_type_t);
	message_len += command_len_len;

	message_len += message.args_len;

	char* message_buffer = new char[message_len];

	memcpy(message_buffer, &message.command, command_len);
	memcpy(message_buffer + command_len, &message.args_len, command_len_len);
	memcpy(message_buffer + command_len + command_len_len, message.command_args,
			message.args_len);

	int sent = 0;

	while (sent < message_len) {
		int bytes_sent = _socket.send_message(message_buffer + sent,
				message_len - sent);

		if (bytes_sent < 0) {
			sent = bytes_sent;
			break;
		}

		sent += bytes_sent;
	}

	delete[] message_buffer;

	if (sent < 0) {
		Logger::customLog("client_handler.cpp", Logger::ERROR,
				"No se pudo enviar el mensaje al cliente");

		return;
	}
}

