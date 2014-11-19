FLDR_ADD=#-Iserver/json

CFLAGS=-Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage $(FLDR_ADD)
EXEC=TheGame
CC= gcc -std=c++11 -g

SRC=$(wildcard *.cpp)
SRC+= $(wildcard */*.cpp)
SRC+= $(wildcard */*/*.cpp)
SRC+= $(wildcard */*/*/*.cpp)
SRC+= $(wildcard */*/*/*/*.cpp)
SRC+= $(wildcard */*/*/*/*/*.cpp)
SRC+= $(wildcard */*/*/*/*/*/*.cpp)

OBJS=$(SRC:.cpp=.o)
LDFLAGS=-lm -lstdc++ -lgcov -coverage -lpthread -pthread  -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

ifneq (,$(shell grep -lm 1 \'^\s*\#.*include.*\<math\.h\>\' *.h *.c ))
	LDFLAGS+=-lm
endif

all: clean $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) *.o -o $(EXEC)

clean:	
	rm -f *.o
	rm -f */*.o
	rm -f */*/*.o
	rm -f */*/*/*.o
	rm -f */*/*/*/*.o
	rm -f */*/*/*/*/*.o
	rm -f */*/*/*/*/*/*.o
	rm -f $(RM_FILES) $(EXEC) *.gcno *.gcda  *~ *.log
