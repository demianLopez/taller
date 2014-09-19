#Project Builder
#General
CC = gcc -std=c++11 -g
CPPFLAGS = -Wall -Wextra -g -pedantic -fprofile-arcs -ftest-coverage
CPPLDFLAGS = -lm -lstdc++ -lgcov -coverage

EXEC = polygons_test

#Graphic libs builder

SDL_CPPFLAGS = $(CPPFLAGS) `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf $(CPPLDFLAGS)

BOX_LDFLAGS = $(SDL_LDFLAGS) -lBox2D

#ALL
VIEW = polygon.o polygon_factory.o regular_polygon.o
MODEL = model_polygon.o model_regular_polygon.o model_rectangle.o model_circle.o model_trapezoid.o model_paralelogram.o model_polygon_factory.o
OBJECTS = $(MODEL) #$(VIEW)

all: $(EXEC)
	
#Model
	
model_polygon.o: libs/polygons/model_polygon/model_polygon.h libs/polygons/model_polygon/model_polygon.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_polygon/model_polygon.cpp

model_regular_polygon.o: libs/polygons/model_regular_polygon/model_regular_polygon.h libs/polygons/model_regular_polygon/model_regular_polygon.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_regular_polygon/model_regular_polygon.cpp
	
model_rectangle.o: libs/polygons/model_rectangle/model_rectangle.h libs/polygons/model_rectangle/model_rectangle.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_rectangle/model_rectangle.cpp

model_trapezoid.o: libs/polygons/model_trapezoid/model_trapezoid.h libs/polygons/model_trapezoid/model_trapezoid.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_trapezoid/model_trapezoid.cpp
	
model_paralelogram.o: libs/polygons/model_paralelogram/model_paralelogram.h libs/polygons/model_paralelogram/model_paralelogram.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_paralelogram/model_paralelogram.cpp

model_circle.o: libs/polygons/model_circle/model_circle.h libs/polygons/model_circle/model_circle.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_circle/model_circle.cpp
	
model_polygon_factory.o: libs/polygons/model_polygon_factory/model_polygon_factory.h libs/polygons/model_polygon_factory/model_polygon_factory.cpp
	$(CC) $(SDL_CPPFLAGS) -c libs/polygons/model_polygon_factory/model_polygon_factory.cpp
	
	

$(EXEC): polygons_tests.cpp $(OBJECTS)
	$(CC) $(BOX_LDFLAGS) $(OBJECTS) polygons_tests.cpp -o $(EXEC)

clean:
	rm -f -r *.o *.save *~ $(EXEC) *.gcno *.gcda
