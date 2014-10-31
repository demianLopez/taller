/*
 * Server.cpp
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#include <Server.h>

void run_server(Accept_queue* queue, list<thread*>* threads,
		list<Client_handler*>* clients, Server * server) {

	while (server->isOnLoop()) {
		if(queue->is_open()){

			Client_handler * client = queue->accept_client();

			std::cout << "as" << std::endl;
			if (client->is_valid()) {
				clients->push_back(client);
				threads->push_back(new thread(Client_handler::execute_listen, client));
			} else {
				delete client;
			}
			server->removeInactives();
		}
	}
	server->removeInactives();

}

Server::Server() {
	// TODO Auto-generated constructor stub

}

void Server::removeInactives(){
	size_t n_client = 0;

	while (n_client < clients.size()) {

		Client_handler * client = clients.front();
		clients.pop_front();

		thread* client_thread = threads.front();
		threads.pop_front();
		std::cout << "B" << std::endl;
		if (!client->is_active()) {
			std::cout << "C" << std::endl;
			client_thread->join();
			client->recicle();
			delete client;
			delete client_thread;
		} else {
			clients.push_back(client);
			threads.push_back(client_thread);
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

		thread* client_thread = threads.front();
		threads.pop_front();

		client->stop();

		client_thread->join();
		client->recicle();
		delete client_thread;
		n_client++;
	}
}

void Server::stopServer(){
	this->serverLoop = false;
	this->stopQueue();
	this->stopClients();
	server_thread.join();
}

bool Server::isOnLoop(){
	return this->serverLoop;
}

void Server::starServer(int port){
	this->serverLoop = true;
	queue.initialize(port);
	server_thread = thread(run_server, &queue, &threads, &clients, this);
}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

