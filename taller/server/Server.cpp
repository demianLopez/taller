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

void Server::waitServerThread(){
	this->server_thread.join();
}

void Server::listen(){
	if(queue.is_open()){

		Client_handler * client = NULL;
		client = queue.accept_client();

		if (client != NULL) {
			this->userListMutex.lock();
			clients.push_back(client);
			client->userIndex = lastIndex;
			lastIndex++;
			client->setDataObserver(new ServerData(this));
			this->removeInactives();
			this->userListMutex.unlock();
		}
	}
}

Server::Server() {
	this->lastIndex = 0;
}

Client_handler * Server::getUser(char userIndex){
	this->userListMutex.lock();
	for(auto * user : clients){
		if(user->userIndex == userIndex){
			return user;
		}
	}
	this->userListMutex.unlock();

	return NULL;
}

void Server::removeInactives(){

	//TODO: DESCONFIO DE LA EFECTIVIDAD DE ESTA FUNCION, TIRA VARIOS SEG FAULT

	for(auto * client : clients){

		std::cout << "B " << client<< std::endl;
		if(client != NULL){
			if (!client->isConnected()) {
				std::cout << "C" << std::endl;

				client->waitThreadEnd();
				std::cout<<"Borr"<<std::endl;
				delete client; //este delete rompe todo!
				client = NULL;
			}
		}

	}
}

void Server::stopQueue(){
	queue.close();
}

void Server::stopClients(){
	for(auto * client : clients){
		if(client != NULL){
			client->stop();
			client->waitThreadEnd();
		}
	}
}

void Server::stopServer(){
	this->serverLoop = false;
	this->stopQueue();
	server_thread.join();
	cout<<"Starting stop"<<endl;
	this->stopClients();
	cout<<"Clients stoped"<<endl;
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

