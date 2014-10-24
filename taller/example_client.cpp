#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <signal.h>

#include "server/accept_queue.h"
#include "server/client_handler.h"

using std::list;
using std::cout;
using std::endl;
using std::thread;

static void send_msj(Socket* socket) {
	int i = 0;
	signal(SIGPIPE, SIG_IGN);
	while (socket->is_valid()) {
		std::cout << "Send" << std::endl;
		int sended = -1;
		if (i % 2) {
			sended = socket->send_message("Hola Munro\0");
		} else {
			sended = socket->send_message("Hola Mundo\0");
		}

		std::cout << sended << std::endl;
		if (sended < 1) {
			std::cerr << "Error de conexion con el Servidor. Desconexion"
					<< std::endl;
			socket->shutdown_socket();
			break;
		}
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	socket->close_port();
}

int main() {
	signal(SIGPIPE, SIG_IGN);
	Socket socket = Socket(8080);
	if (!socket.is_valid())
		return 1;
	std::cout << "AND" << std::endl;
	thread client_thread = thread(send_msj, &socket);
	while (socket.is_valid()&&fgetc(stdin) != EOF);
	socket.shutdown_socket();
	client_thread.join();
	return 0;
}
