#Project Builder
#General
CC = gcc -std=c++11
CPPFLAGS = -Wall -Wextra -g -pedantic
CPPLDFLAGS = -lm -lstdc++

EXEC = Snowbros

#Graphic libs builder

SDL_CPPFLAGS = $(CPPFLAGS) `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf $(CPPLDFLAGS)

BOX_LDFLAGS = $(SDL_LDFLAGS) -lBox2D

#ALL
OBJECTS = $(GRAPHIC_LIBS)

all: $(EXEC) 