#include <list>
#include <iostream>
#include <thread>
#include <chrono>

#include "server/accept_queue.h"
#include "server/client_handler.h"

using std::list;
using std::cout;
using std::endl;
using std::thread;

static void send_msj(Socket* socket) {
	int i = 0;
	while (socket->is_valid()) {
		std::cout << "Send" << std::endl;
		int sended = 0;
		if (i % 2) {
			sended = socket->send_message("Hola Munro\0");
		} else {
			sended = socket->send_message("Hola Mundo\0");
		}

		if (sended < 1) {
			std::cerr << "Error de conexion con el Servidor. Desconexion"
					<< std::endl;
			break;
		}
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	socket->close_port();
}

int main() {

	Socket socket = Socket(8080);
	if (!socket.is_valid())
		return 1;
	std::cout << "AND" << std::endl;
	thread client_thread = thread(send_msj, &socket);
	while (fgetc(stdin) != EOF && socket.is_valid());
	socket.shutdown_socket();
	client_thread.join();
	return 0;
}
