#include <list>
#include <iostream>
#include <thread>

#include "server/accept_queue.h"
#include "server/client_handler.h"

using std::list;
using std::cout;
using std::endl;
using std::thread;


typedef Client_handler* client_t; //TODO: cambiar

void remove_inactives(list<client_t>& clients, list<thread*> threads) {
	size_t n_client = 0;
	std::cout << "A" << std::endl;

	while (n_client < clients.size()) {
		std::cout << "B" << std::endl;

		client_t client = clients.front();
		clients.pop_front();
		thread* client_thread = threads.front();
		threads.pop_front();
		if (!client->is_active()) {
			std::cout << "C" << std::endl;

			client_thread->join();
			client->recicle();
			delete client;
		} else {
			clients.push_back(client);
			threads.push_back(client_thread);
		}

		n_client++;
	}
}

void stop_clients(list<client_t> clients, list<thread*> threads) {
	size_t n_client = 0;
	while (n_client < clients.size()) {
		client_t client = clients.front();
		clients.pop_front();

		thread* client_thread = threads.front();
		threads.pop_front();

		client->stop();

		client_thread->join();
		client->recicle();
		n_client++;
	}
}

int main() {
	Accept_queue queue;
	list<client_t> clients;
	list<thread*> threads;

	queue.initialize();

	int i = 0;
	while (i < 3) {
		client_t client = queue.accept_client();
		if (client->is_valid()) {
			clients.push_back(client);
			threads.push_back(new thread(Client_handler::execute,client));
		}

		remove_inactives(clients, threads);
		i++;
	}

	stop_clients(clients, threads);
	return 0;
}
