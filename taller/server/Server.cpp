/*
 * Server.cpp
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#include "Server.h"
#include "ServerData.h"

void Server::run_server(Server * server) {
	while (server->isOnLoop()) {
		server->listen();
	}
}

void Server::waitServerThread() {
	this->server_thread.join();
}

void Server::listen() {
	if (queue.is_open()) {

		Socket * newConection = NULL;
		newConection = queue.accept_client();

		if (newConection != NULL) {
			this->userListMutex.lock();

			for (auto * client : clients) {
				if (client->isEmpty()) {
					client->setSocket(newConection);
					client->startLoop();
					client->userIndex = lastIndex;
					lastIndex++;

					break;
				}
			}
			this->userListMutex.unlock();
		}
	}
}

Server::Server() {
	this->lastIndex = 0;
	this->maxConnections = 8;
}

Client_handler * Server::getUser(char userIndex) {
	this->userListMutex.lock();
	for (auto * user : clients) {
		if (user->userIndex == userIndex) {
			return user;
		}
	}
	this->userListMutex.unlock();

	return NULL;
}

void Server::stopQueue() {
	queue.close();
}

void Server::stopClients() {
	for (auto * client : clients) {
		if (!client->isEmpty()) {
			client->stop();
		}
		client->waitThreadEnd();
		delete client;
	}
}

void Server::stopServer() {
	this->serverLoop = false;
	this->stopQueue();
	server_thread.join();
	this->stopClients();
}

void Server::sendToAll(Message * message) {
	for (auto * user : clients) {
		if (user->isConnected()) {
			user->send_message(message);
		}
	}
}

void Server::sendToOthers(Message * message, int userIndex) {
	for (auto * user : clients) {
		if (user->isConnected() && (user->userIndex != userIndex)) {
			user->send_message(message);
		}
	}
}

bool Server::isOnLoop() {
	return this->serverLoop;
}

void Server::starServer(int port) {
	for (int i = 0; i < this->maxConnections; i++) {
		Client_handler * client = new Client_handler();
		clients.push_back(client);
		client->setDataObserver(new ServerData(this));
	}

	this->serverLoop = true;
	queue.initialize(port);
	server_thread = thread(Server::run_server, this);
}

Server::~Server() {
}

