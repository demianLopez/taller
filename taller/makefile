#Project Builder
#General
CC = gcc -std=c++11 -g
CPPFLAGS = -Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage
CPPLDFLAGS = -lm -lstdc++ -lgcov -coverage -lpthread -pthread

#ALL
CLIENT_O = $(COMMON_O)

all: server client

client: $(CLIENT_O)
	$(CC) $(CPPFLAGS) $(CPPLDFLAGS) $(CLIENT_O) example_client.cpp -o Client
	
client_handler.o: server/client_handler.h server/client_handler.cpp
	$(CC) $(CPPLDFLAGS) -c server/client_handler.cpp
	
clean:
	rm -f *.o *.gcno *.gcda  *~ Client Server
