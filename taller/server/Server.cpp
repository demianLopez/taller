/*
 * Server.cpp
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#include <Server.h>
#include "ServerData.h"

void Server::run_server(Server * server) {
	while (server->isOnLoop()) {
		server->listen();
	}
}

void Server::listen(){
	if(queue.is_open()){

		Client_handler * client = NULL;
		client = queue.accept_client();

		if (client != NULL) {
			clients.push_back(client);
			client->setDataObserver(new ServerData(this));
			this->removeInactives();
		}
	}
}

Server::Server() {
	// TODO Auto-generated constructor stub

}

void Server::removeInactives(){
	size_t n_client = 0;

	while (n_client < clients.size()) {

		Client_handler * client = clients.front();
		clients.pop_front();

		std::cout << "B" << std::endl;
		if (!client->isConnected()) {
			std::cout << "C" << std::endl;
			delete client;
		} else {
			clients.push_back(client);
		}

		n_client++;
	}
}

void Server::stopQueue(){
	queue.close();
}


void Server::stopClients(){
	size_t n_client = 0;
	while (n_client < clients.size()) {
		Client_handler * client = clients.front();
		clients.pop_front();
		client->stop();
		n_client++;
	}
}

void Server::stopServer(){
	this->serverLoop = false;
	this->stopQueue();
	this->stopClients();
	server_thread.join();
	this->removeInactives();
}

bool Server::isOnLoop(){
	return this->serverLoop;
}

void Server::starServer(int port){
	this->serverLoop = true;
	queue.initialize(port);
	server_thread = thread(Server::run_server, this);
}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

