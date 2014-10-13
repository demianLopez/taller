#include <list>
#include <iostream>
#include <thread>

#include "server/accept_queue.h"
#include "server/client_handler.h"

using std::list;
using std::cout;
using std::endl;
using std::thread;


typedef Client_handler client_t; //TODO: cambiar



int main() {
	Accept_queue queue;
	list<client_t> clients;
	list<thread*> threads;

	queue.initialize();

	int i = 0;
	while (i < 2) {
		client_t client = queue.accept_client();
		if (client.is_valid()) {
			clients.push_back(client);
			threads.push_back(new thread(Client_handler::execute,client));
		}

		size_t n_client = 0;
		while (n_client < clients.size()) {
			client_t client = clients.front();
			clients.pop_front();

			thread* client_thread = threads.front();
			threads.pop_front();
			if (!client.is_active()) {
				client_thread->join();
				client.recicle();
			} else {
				clients.push_back(client);
			}
		}
		i++;
	}
	return 0;
}
