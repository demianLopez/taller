#include <list>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <signal.h>

#include "common/message_command.h"
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

void handle_connection_error(Socket* socket) {
	std::cerr << "Error de conexion con el cliente. Desconexion" << std::endl;
	socket->shutdown_socket();
}

static void recv_msj(Socket* socket, std::mutex* std_out_mutex) {
	signal(SIGPIPE, SIG_IGN);
	while (socket->is_valid()) {
		//Obtengo el comando
		size_t command_len = sizeof(command_id_type_t);
		char* command_buffer = new char [command_len];
		int bytes_read = 0;
		while(bytes_read < command_len){
			int read = socket->receive(command_buffer+bytes_read, command_len-bytes_read);
			if (read<0){
				bytes_read = read;
				break;
			}
			bytes_read += read;
		}

		if (bytes_read < 0) {
			handle_connection_error(socket);
			break;
		}

		command_id_type_t command = *((command_id_type_t*)command_buffer);


		//Obtengo la longitud de los parametros
		size_t command_len_len = sizeof(command_len_type_t);
		char* command_len_buffer = new char [command_len_len];
		bytes_read = 0;
		while(bytes_read < command_len_len){
			int read = socket->receive(command_len_buffer+bytes_read, command_len_len-bytes_read);
			if (read<0){
				bytes_read = read;
				break;
			}
			bytes_read += read;
		}

		if (bytes_read < 0) {
			handle_connection_error(socket);
			break;
		}

		command_len_type_t args_len = *((command_len_type_t*)command_len_buffer);


		//Obtengo los parametros
		char* args_buffer = new char [args_len+10];
		bytes_read = 0;
		while(bytes_read < args_len){
			int read = socket->receive(args_buffer+bytes_read, args_len-bytes_read);
			if (read<0){
				bytes_read = read;
				break;
			}
			bytes_read += read;
		}

		if (bytes_read < 0) {
			handle_connection_error(socket);
			break;
		}

		command_args_type_t args = (command_args_type_t)args_buffer;

		//DEBUG

		int a = command;
		int b = args_len;
		char* c = (char*)args;

		c[bytes_read] = '\0';
		std::string mess = std::string(c);

		std_out_mutex->lock();
		std::cout << "Comando: " << a << std::endl;
		std::cout << "Arg len: " << b << std::endl;
		std::cout << "Args   : " << mess << std::endl;
		std_out_mutex->unlock();

		//DEBUG

		delete[] command_buffer;
		delete[] command_len_buffer;
		delete[] args_buffer;

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
