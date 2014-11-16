CFLAGS=-Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage
EXEC=enemies_test
CC= gcc -std=c++11 -g
SRC+= $(wildcard server/bonus_items/*.cpp)
SRC+= $(wildcard server/level_objects/*.cpp)
SRC+= $(wildcard server/level_objects/collision_strategies/*.cpp)
SRC+= $(wildcard server/moving_objects/*.cpp)
SRC+= $(wildcard server/moving_objects/move_patterns/*.cpp)
SRC+= $(wildcard server/weapons/*.cpp)
SRC+= $(wildcard server/weapons/projectile/*.cpp)


OBJS=$(SRC:.cpp=.o)
LDFLAGS=-lm -lstdc++ -lgcov -coverage -lpthread -pthread

ifneq (,$(shell grep -lm 1 \'^\s*\#.*include.*\<math\.h\>\' *.h *.cpp ))
	LDFLAGS+=-lm
endif

all: clean $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -f *.o
	rm -f */*.o
	rm -f */*/*.o	
	rm -f */*/*/*.o
	rm -f */*/*/*/*.o
	
	rm -f $(RM_FILES) $(EXEC) *.gcno *.gcda  *~