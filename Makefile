#Project Builder
#General
CC = gcc -std=c++11
CPPFLAGS = -Wall -Wextra -g -pedantic 
CPPLDFLAGS = -lm -lstdc++

EXEC = test

OBJECTS = RGB_parser.o

all: $(EXEC) 
		
RGB_parser.o: libs/RGB_parser/RGB_parser.h libs/RGB_parser/RGB_parser.cpp
	$(CC) $(CPPFLAGS) -c libs/RGB_parser/RGB_parser.cpp
				
$(EXEC): parser_test.cpp $(OBJECTS)
	$(CC) $(CPPLDFLAGS) $(OBJECTS) parser_test.cpp -o $(EXEC)

clean:
	rm -r *.o *.save *~ $(EXEC)