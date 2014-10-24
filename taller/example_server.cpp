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

	while (n_client < clients.size()) {

		client_t client = clients.front();
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

void stop_clients(list<client_t>& clients, list<thread*>& threads) {
	size_t n_client = 0;
	while (n_client < clients.size()) {
		client_t client = clients.front();
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

void run_server(Accept_queue* queue, list<thread*>* threads,
		list<client_t>* clients) {

	while (queue->is_open()) {
		client_t client = queue->accept_client();

		std::cout << "a" << std::endl;
		if (client->is_valid()) {
			clients->push_back(client);
			threads->push_back(new thread(Client_handler::execute, client));
		}else{
			delete client;
		}
		remove_inactives(*clients, *threads);
	}
}

void stop_queue(Accept_queue& queue){
	queue.close();
}

int main() {
	Accept_queue queue;
	list<client_t> clients;
	list<thread*> threads;

	queue.initialize();

	thread server_thread = thread(run_server, &queue, &threads, &clients);

	while (fgetc(stdin) != EOF);
	stop_queue(queue);
	stop_clients(clients, threads);
	server_thread.join();
	return 0;
}
