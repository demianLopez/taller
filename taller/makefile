#Project Builder
#General
CC = gcc -std=c++11 -g
CPPFLAGS = -Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage
CPPLDFLAGS = -lm -lstdc++ -lgcov -coverage -lpthread -pthread

#ALL
OBJECTS = enemy.o enemy_factory.o level_object.o

all: test

test: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(CPPLDFLAGS) $(OBJECTS) enemies_test.cpp -o test

level_object.o: server/level_objects/level_object.h server/level_objects/level_object.cpp
	$(CC) $(CPPLDFLAGS) -c server/level_objects/level_object.cpp
	
enemy.o: server/enemies/enemy.h server/enemies/enemy.cpp
	$(CC) $(CPPLDFLAGS) -c server/enemies/enemy.cpp
	
enemy_factory.o: server/enemies/enemy_factory.h server/enemies/enemy_factory.cpp
	$(CC) $(CPPLDFLAGS) -c server/enemies/enemy_factory.cpp
	
clean:
	rm -f *.o *.gcno *.gcda  *~ test
