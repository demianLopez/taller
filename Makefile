#Project Builder
#General
CC = gcc -std=c++11
CPPFLAGS = -Wall -Wextra -g -pedantic
CPPLDFLAGS = -lm -lstdc++

EXEC = polygons_test

#Graphic libs builder

SDL_CPPFLAGS = $(CPPFLAGS) `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf $(CPPLDFLAGS)

BOX_LDFLAGS = $(SDL_LDFLAGS) -lBox2D

#ALL
OBJECTS = polygon.o polygon_factory.o regular_polygon.o

all: $(EXEC)

polygon.o: libs/polygons/polygon/polygon.h libs/polygons/polygon/polygon.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/polygon/polygon.cpp

regular_polygon.o: libs/polygons/regular_polygon/regular_polygon.h libs/polygons/regular_polygon/regular_polygon.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/regular_polygon/regular_polygon.cpp
	
polygon_factory.o: libs/polygons/polygon_factory/polygon_factory.h libs/polygons/polygon_factory/polygon_factory.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/polygon_factory/polygon_factory.cpp

$(EXEC): polygons_tests.cpp $(OBJECTS)
	$(CC) $(BOX_LDFLAGS) $(OBJECTS) polygons_tests.cpp -o $(EXEC)

clean:
	rm -r *.o *.save *~ $(EXEC)