/**
 model_circle.cpp

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
#include "model_circle.h"

Model_circle::~Model_circle() {
	// TODO Auto-generated destructor stub
}

Model_circle::Model_circle(double diameter, double density, int body_type,
		b2World& world) :
		Model_polygon(body_type, density) {

	b2CircleShape circle_shape;
	circle_shape.m_p.Set(0, 0);

	float32 radius = diameter/2;
	circle_shape.m_radius = radius;

	b2FixtureDef body_fixture;
	body_fixture.shape = &circle_shape;

	b2BodyDef body_definition;
	body_definition.position.Set(0, 0); //seteo posicion base

	Model_polygon::create_body(&body_definition, &body_fixture, world);
}
