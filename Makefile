#Project Builder
#General
CC = gcc -std=c++11
CPPFLAGS = -Wall -Wextra -g -pedantic 
CPPLDFLAGS = -lm -lstdc++

EXEC = test

OBJECTS = logger.o

all: $(EXEC) 
		
logger.o: libs/logger/logger.h libs/logger/logger.cpp
	$(CC) $(CPPFLAGS) -c libs/logger/logger.cpp
				
$(EXEC): logger_test.cpp $(OBJECTS)
	$(CC) $(CPPLDFLAGS) $(OBJECTS) logger_test.cpp -o $(EXEC)

clean:
	rm -r *.o *.save *~ $(EXEC)