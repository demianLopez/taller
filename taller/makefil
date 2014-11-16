#Project Builder
#General
CC = gcc -std=c++11 -g
CPPFLAGS = -Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage
CPPLDFLAGS = -lm -lstdc++ -lgcov -coverage -lpthread -pthread

#ALL
OBJECTS = enemy.o enemy_factory.o level_object.o standar_weapon.o weapon.o

all: test

test: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(CPPLDFLAGS) $(OBJECTS) enemies_test.cpp -o test

level_object.o: server/level_objects/level_object.h server/level_objects/level_object.cpp
	$(CC) $(CPPLDFLAGS) -c server/level_objects/level_object.cpp
	
enemy.o: server/enemies/enemy.h server/enemies/enemy.cpp
	$(CC) $(CPPLDFLAGS) -c server/enemies/enemy.cpp
	
weapon.o: server/weapons/weapon.h server/weapons/weapon.cpp
	$(CC) $(CPPLDFLAGS) -c server/weapons/weapon.cpp
	
standar_weapon.o: server/weapons/standar_weapon.h server/weapons/standar_weapon.cpp
	$(CC) $(CPPLDFLAGS) -c server/weapons/standar_weapon.cpp
	
enemy_factory.o: server/enemies/enemy_factory.h server/enemies/enemy_factory.cpp
	$(CC) $(CPPLDFLAGS) -c server/enemies/enemy_factory.cpp
	
clean:
	rm -f *.o *.gcno *.gcda  *~ test
