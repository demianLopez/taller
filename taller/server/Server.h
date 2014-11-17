/*
 * Server.h
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "accept_queue.h"
#include "../common/client_handler.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "../common/Message.h"

using std::vector;
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

	void waitServerThread();

	Client_handler * getUser(char userIndex);

	//Envia el mensaje a todos
	void sendToAll(Message * message);

	//Envia el mensaje a todos menos a "me"
	void sendToOthers(Message * message, int userIndex);

	virtual ~Server();
private:

	void listen();
	void stopQueue();
	void stopClients();

	Accept_queue queue;

	vector<Client_handler *> clients;

	thread server_thread;

	bool serverLoop;

	static void run_server(Server * server);

	mutex userListMutex;

	char lastIndex;

	int maxConnections;
};

#endif /* SERVER_H_ */
