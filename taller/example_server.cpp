#include <list>
#include <iostream>

#include "server/accept_queue.h"
#include "server/client_handler.h"

using std::list;
using std::cout;
using std::endl;

typedef Client_handler client_t; //TODO: cambiar

int remove_inactive(list<client_t>& clients) {
	size_t n_client = 0;
	while (n_client < clients.size()) {
		client_t client = clients.front();
		clients.pop_front();
		if (!client.is_active()) {
			client.recicle();
		} else {
			clients.push_back(client);
		}
	}
	return n_client;
}

int main() {
	Accept_queue queue;
	list<client_t> clients;

	queue.initialize();

	int i = 0;
	while (i < 2) {
		client_t client = queue.accept_client();
		if (client.is_valid()){
		clients.push_back(client);
		}

		int n_client = remove_inactive(clients);
		i++;
	}
	return 0;
}
