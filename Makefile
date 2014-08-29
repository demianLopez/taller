#Project Builder
#General
CC = gcc
CPPFLAGS = -Wall -Wextra -g -pedantic
CPPLDFLAGS = -lm -lstdc++

EXEC = Snowbros

#Graphic libs builder

SDL_CPPFLAGS = $(CPPFLAGS) `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf $(CPPLDFLAGS)

GRAPHIC_LIBS = sprite.o window.o


#ALL
OBJECTS = $(GRAPHIC_LIBS)

all: $(EXEC) 
		
sprite.o: sprite/sprite.h sprite/sprite.cpp
	$(CC) $(SDL_CPPFLAGS) -c sprite/sprite.cpp
		
window.o: window/window.h window/window.cpp
	$(CC) $(SDL_CPPFLAGS) -c window/window.cpp
		
$(EXEC): jump_test.cpp $(OBJECTS)
	$(CC) $(SDL_LDFLAGS) $(OBJECTS) jump_test.cpp -o $(EXEC)

clean:
	rm -r *.o *.save *~ $(EXEC)