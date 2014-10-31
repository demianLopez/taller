/*
 * Client.cpp
 *
 *  Created on: 30/10/2014
 *      Author: demian
 */

#include <Client.h>

static void send_msj(Client * client ) {

	signal(SIGPIPE, SIG_IGN);

	while (client->isConnected()) {
		client->send("Hola mundo\0", 10);
	}

}

Client::Client() {
	// TODO Auto-generated constructor stub

}

bool Client::isConnected(){
	return this->connected;
}

void Client::send(const char * msg, int size){
	if(socket.is_valid()){
		int sent = -1;
		sent = socket.send_message(msg);

		if (sent < 1) {
			std_out_mutex.lock();
			std::cout << "Se perdio la conexion con el servidor!"
					<< std::endl;
			std_out_mutex.unlock();
			socket.shutdown_socket();
		}
	}
}

void Client::disconnect(){
	socket.shutdown_socket();
	client_thread_a.join();
	socket.close_port();
	this->connected = false;
	//client_thread_b.join();
}

void Client::connect(int port){

	signal(SIGPIPE, SIG_IGN);
	socket = Socket(port);
	if (!socket.is_valid())
		return;

	this->connected = true;
	client_thread_a = thread(send_msj, this);

	//client_thread_b = thread(recv_msj, &socket, &std_out_mutex);
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

