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

void set_point(double& x, double& y, double radians) {
	x = cos(radians);
	y = sin(radians);
}

void define_vertex(size_t sides, b2Vec2* vertex) {
	double perimeter = 2 * M_PI;
	double segment_size = perimeter / sides;
	double traveled_perimeter = 0;
	double x = 0, y = 0;
	for (size_t i; i < sides; i++) {
		vertex[i].Set(x, y);
		traveled_perimeter += segment_size;
		set_point(x, y, traveled_perimeter);
	}
}

void scale_vertex(size_t sides, b2Vec2* vertex, double scale) {
	for (size_t i; i < sides; i++) {
		double x = vertex[i].x;
		double y = vertex[i].y;
		x *= scale;
		y *= scale;
		vertex[i].Set(x, y);
	}
}

Model_regular_polygon::Model_regular_polygon(size_t sides, double scale,
		int body_type, double density, b2World& world) :
		Model_polygon(body_type, density) {

	b2Vec2* vertex = new b2Vec2[sides];
	define_vertex(sides, vertex);

	scale_vertex(sides, vertex, scale);

	b2PolygonShape polygon_shape;
	polygon_shape.Set(vertex, sides); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &polygon_shape;

	b2BodyDef body_definition;
	body_definition.position.Set(0, 0); //seteo posicion base

	Model_polygon::create_body(&body_definition, &body_fixture, world);

	delete[] vertex;
}

Model_regular_polygon::~Model_regular_polygon() {
}

