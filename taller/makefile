#Project Builder
#General
CC = gcc -std=c++11 -g
CPPFLAGS = -Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage
CPPLDFLAGS = -lm -lstdc++ -lgcov -coverage -lpthread -pthread

#ALL
COMMON_O = socket.o
SERVER_O = $(COMMON_O) accept_queue.o client_handler.o
CLIENT_O = $(COMMON_O)

all: server

server: $(SERVER_O) example_server.cpp
	$(CC) $(CPPFLAGS) $(CPPLDFLAGS) $(SERVER_O) example_server.cpp -o Server
	
client: $(CLIENT_O)
	$(CC) $(CPPFLAGS) $(CPPLDFLAGS) $(CLIENT_O) example_client.cpp -o Client
	
socket.o: common/socket.h common/socket.cpp
	$(CC) $(CPPLDFLAGS) -c common/socket.cpp

accept_queue.o: server/accept_queue.h server/accept_queue.cpp
	$(CC) $(CPPLDFLAGS) -c server/accept_queue.cpp
	
client_handler.o: server/client_handler.h server/client_handler.cpp
	$(CC) $(CPPLDFLAGS) -c server/client_handler.cpp
	
clean:
	rm -f *.o *.gcno *.gcda  *~
