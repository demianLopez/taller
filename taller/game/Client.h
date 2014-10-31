/*
 * Client.h
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <list>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <signal.h>

#include "../common/message_command.h"
#include "../server/accept_queue.h"
#include "../server/client_handler.h"

using std::list;
using std::cout;
using std::endl;
using std::thread;
using std::mutex;

class Client {
public:
	Client();
	void connect(int port);
	void disconnect();
	void send(const char * msg, int size);

	bool isConnected();

	virtual ~Client();
private:
	thread client_thread_a;
	thread client_thread_b;

	bool connected;

	Socket socket;
	std::mutex std_out_mutex;
};

#endif /* CLIENT_H_ */
