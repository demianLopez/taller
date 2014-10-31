/*
 * Server.h
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "accept_queue.h"
#include "client_handler.h"
#include <list>
#include <iostream>
#include <thread>
#include <chrono>

using std::list;
using std::cout;
using std::endl;
using std::thread;

class Server {
public:
	Server();
	void starServer(int port);
	bool isOnLoop();

	void stopServer();

	void removeInactives();

	virtual ~Server();
private:

	void stopQueue();
	void stopClients();

	Accept_queue queue;
	list<Client_handler *> clients;
	list<thread *> threads;

	thread server_thread;

	bool serverLoop;
};

#endif /* SERVER_H_ */
