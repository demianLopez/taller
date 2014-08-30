#Project Builder
#General
CC = gcc
CPPFLAGS = -Wall -Wextra -g -pedantic
CPPLDFLAGS = -lm -lstdc++

EXEC = Snowbros

#Graphic libs builder

SDL_CPPFLAGS = $(CPPFLAGS) `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf $(CPPLDFLAGS)

BOX_LDFLAGS = $(SDL_LDFLAGS) -lBox2D

GRAPHIC_LIBS = sprite.o window.o

#ALL
OBJECTS = $(GRAPHIC_LIBS)

all: $(EXEC) 
		
sprite.o: libs/sprite/sprite.h libs/sprite/sprite.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/sprite/sprite.cpp
		
window.o: libs/window/window.h libs/window/window.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/window/window.cpp
		
$(EXEC): jump_test.cpp $(OBJECTS)
	$(CC) $(BOX_LDFLAGS) $(OBJECTS) jump_test.cpp -o $(EXEC)

clean:
	rm -r *.o *.save *~ $(EXEC)