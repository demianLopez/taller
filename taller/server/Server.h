/*
 * Server.h
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "accept_queue.h"
#include <client_handler.h>
#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using std::list;
using std::cout;
using std::endl;
using std::thread;
using std::mutex;

class Server {
public:
	Server();
	void starServer(int port);
	bool isOnLoop();

	void stopServer();

	void removeInactives();


	void waitServerThread();

	Client_handler * getUser(char userIndex);

	virtual ~Server();
private:

	void listen();
	void stopQueue();
	void stopClients();

	Accept_queue queue;
	list<Client_handler *> clients;

	thread server_thread;

	bool serverLoop;

	static void run_server(Server * server);

	mutex userListMutex;

	char lastIndex;
};

#endif /* SERVER_H_ */
