#include <list>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <signal.h>

#include "server/accept_queue.h"
#include "server/client_handler.h"

using std::list;
using std::cout;
using std::endl;
using std::thread;
using std::mutex;

static void send_msj(Socket* socket, std::mutex* std_out_mutex) {
	int i = 0;
	signal(SIGPIPE, SIG_IGN);
	while (socket->is_valid()) {
		int sent = -1;
		if (i % 2) {
			sent = socket->send_message("Hola Munro\0");
		} else {
			sent = socket->send_message("Hola Mundo\0");
		}

		std_out_mutex->lock();
		std::cout << "Se enviaron:" << sent << "bytes." << std::endl;
		std_out_mutex->unlock();

		if (sent < 1) {
			std_out_mutex->lock();
			std::cout << "Error de conexion con el Servidor. Desconexion"
					<< std::endl;
			std_out_mutex->unlock();
			socket->shutdown_socket();
			break;
		}
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	socket->close_port();
}

static void recv_msj(Socket* socket, std::mutex* std_out_mutex) {
	signal(SIGPIPE, SIG_IGN);
	while (socket->is_valid()) {
		char message[10];
		//Send from socket
		int bytes_read = socket->receive(message, 11);

		if (bytes_read < 0) {
			std::cerr << "Error de conexion con el cliente. Desconexion"
					<< std::endl;
			socket->shutdown_socket();
			break;
		}

		message[bytes_read] = '\0';

		std::string mess = std::string(message);

		std_out_mutex->lock();
		std::cout << "Somebody told me: " << mess << std::endl;
		std_out_mutex->unlock();

	}
	socket->close_port();
}

int main() {
	signal(SIGPIPE, SIG_IGN);
	Socket socket = Socket(8080);
	if (!socket.is_valid())
		return 1;
	std::cout << "AND" << std::endl;

	std::mutex std_out_mutex;

	thread client_thread_a = thread(send_msj, &socket, &std_out_mutex);
	thread client_thread_b = thread(recv_msj, &socket, &std_out_mutex);

	while (socket.is_valid() && fgetc(stdin) != EOF)
		;
	socket.shutdown_socket();
	client_thread_a.join();
	client_thread_b.join();

	return 0;
}
