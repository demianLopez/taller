/**
 RegularPolygon.cpp

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

#include "RegularPolygon.h"

void define_vertex(size_t sides, b2Vec2* vertex) {
	double perimeter = 2 * 3.14f;
	for (size_t i = 0; i < sides; i++) {
		double angle = perimeter/sides * i;
		vertex[i].Set(cos(angle), sin(angle));
	}
}

void scale_vertex(size_t sides, b2Vec2* vertex, double scale) {
	for (size_t i = 0; i < sides; i++) {
		double x = vertex[i].x;
		double y = vertex[i].y;
		x *= scale;
		y *= scale;
		vertex[i].Set(x, y);
	}
}

RegularPolygon::RegularPolygon(size_t sides, double scale, double posX, double posY,
		int body_type, double density, World * world) :
		Polygon(body_type) {

	b2Vec2* vertex = new b2Vec2[sides];
	define_vertex(sides, vertex);

	//scale_vertex(sides, vertex, scale);

	b2PolygonShape polygon_shape;
	polygon_shape.Set(vertex, sides); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &polygon_shape;
	body_fixture.density = density;
	body_fixture.friction = friction;

	b2BodyDef body_definition;

	if(body_type == Polygon::STATIC){
		body_definition.type = b2_staticBody;
	} else {
		body_definition.type = b2_dynamicBody;
	}

	body_definition.position.Set(posX, posY); //seteo posicion base

	Polygon::create_body(&body_definition, &body_fixture, world);

	//SDL

	this->setSDLVertex(sides, vertex);
	this->createSDLPoints();

	delete[] vertex;
}

void RegularPolygon::setSDLVertex(size_t sides, b2Vec2 * vertex){
	for (size_t i = 0; i < sides; i++) {
		this->addB2DPoint(vertex[i].x, vertex[i].y);
	}
}

RegularPolygon::~RegularPolygon() {
}

