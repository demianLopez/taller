/**
 model_regular_polygon.cpp

 Copyright 2014 Gaston Martinez Gaston.martinez.90@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses
 */
#define _USE_MATH_DEFINES
#include <math.h>

#include "model_regular_polygon.h"

Model_regular_polygon::Model_regular_polygon(size_t edges, b2World* world) {
	double perimeter = 2 * M_PI;
	double segment_size = perimeter / edges;

	//parametrizar

	b2Vec2 vertex[edges];
	for (int i; i < edges; i++) {
		vertex[i].Set(0, 0);
	}

	b2PolygonShape polygon_shape;
	polygon_shape.Set(vertex, edges); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &polygon_shape;

	b2BodyDef body_definition;
	body_definition.position.Set(0, 0); //seteo posicion base

	this->body = world->CreateBody(&body_definition);
	this->body->CreateFixture(&body_fixture); //add a fixture to the body
}

Model_regular_polygon::~Model_regular_polygon() {
	// TODO Auto-generated destructor stub
}

