/**
 model_rectangle.cpp

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
#include "model_rectangle.h"

Model_rectangle::Model_rectangle(double height, double widht, double density,
		int body_type, b2World& world):Model_polygon(body_type,density) {

	b2PolygonShape box_shape;
	box_shape.SetAsBox(1,1); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;

	b2BodyDef body_definition;
	body_definition.position.Set(0, 0); //seteo posicion base

	Model_polygon::create_body(&body_definition, &body_fixture, world);
}

Model_rectangle::~Model_rectangle() {
	// TODO Auto-generated destructor stub
}

