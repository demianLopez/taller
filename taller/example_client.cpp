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

int main() {

	Socket socket = Socket(8080);
	if (!socket.is_valid())
		return 1;

	int i = 0;
	while (fgetc(stdin) != EOF) {
		if (i % 2) {
			socket.send_message("Hola Munro");
		} else {
			socket.send_message("Hola Mundo");
		}
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	}
	socket.close_port();
	return 0;
}
