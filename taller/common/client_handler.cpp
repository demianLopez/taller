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
	//signal(SIGPIPE, SIG_IGN);
	while (client->isConnected()) {
		if (!client->runListen()) {
			client->stop();
		}
	}
}

void Client_handler::waitThreadEnd() {
	if(this->clientThread.joinable()){
		this->clientThread.join();
	}
}

void Client_handler::startLoop(){
	this->threadLoop = true;
	this->waitThreadEnd();
	this->clientThread = thread(Client_handler::threadFunction, this);
}

Client_handler::Client_handler() {
	this->_socket = NULL;
	this->dataObserver = NULL;
	this->threadLoop = false;
	this->userIndex = 0;
}

bool Client_handler::isEmpty(){
	return !this->threadLoop;
}

void Client_handler::setSocket(Socket * socket){
	this->_socket = socket;
}

Client_handler::~Client_handler() {
	if (dataObserver != NULL) {
		delete dataObserver;
		dataObserver = NULL;
	}
}

bool Client_handler::is_valid() {
	return this->_socket->is_valid(); //TODO: agregar mas condiciones
}

void Client_handler::setDataObserver(DataObserver * dO) {
	this->dataObserver = dO;
}

bool Client_handler::runListen() {
	//Threadear la escucha que es lo que pasa menos seguido
	char message[256];

	char l[5] = {0,0,0,0,0};
	int bytes_read;

	bytes_read = this->_socket->receive(l, 1);

	int need = -1;
	if(bytes_read > 0) need = l[0];

	int readed = 0;
	int toRead = need;

	while(readed < need && bytes_read > 0){

		bytes_read = this->_socket->receive(&message[readed], toRead);
		readed += bytes_read;
		toRead -= bytes_read;
	}

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
		if (dataObserver != NULL) {
			dataObserver->closeConnection(this);
		} else {
			std::cout << "Se perdio la conexion" << std::endl;
		}

		return false;
	}

	if (bytes_read > 0) {
		message[bytes_read] = '\0';

		if (dataObserver != NULL) {
			Message * m = new Message(message, bytes_read);
			try {
				char c = dataObserver->dataArribal(m, this);

				if(m->getCommandCode() != END_CHAR && c != CLOSING_GAME){
					std::cout<<"!WARNING NOT END CHAR FUND ON cCode "<<(int)c<<std::endl;
				}
				delete m;
			} catch (const std::exception&e){
				std::cout<<e.what()<<" - "<<"producido en DataArribal - cCode: "<<m->getFirstCommandCode()<<std::endl;
				exit(-1);
			}
		}
	}
	return true;
}

bool Client_handler::isConnected() {
	return this->threadLoop;
}

void Client_handler::stop() {
	if(!threadLoop){
		return;
	}
	this->threadLoop = false;
	_socket->shutdown_socket();
	_socket->close_port();
	delete _socket;
}

bool Client_handler::send_message(Message * msg){
	//this->sendingMutex.lock();
	if(_socket && _socket->is_valid()){
		int sent = -1;

		sent = _socket->send_message(msg->getMessageData(),
				msg->getMessageLength());

		if(sent < msg->getMessageLength()){
			std::cout<<"WARNING: SEND "<<sent<<" OF "<<msg->getMessageLength()<<std::endl;
		}

		if (sent < 1) {
			this->stop();
			//this->sendingMutex.unlock();
			return false;
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(0));
		//this->sendingMutex.unlock();
		return true;
	}
	//this->sendingMutex.unlock();
	return false;
}
