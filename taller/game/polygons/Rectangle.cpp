/**
 Rectangle.cpp

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
#include "Rectangle.h"



Rectangle::Rectangle(double width, double height, double density, double posX, double posY, double angle,
		int body_type, World * world):Polygon(body_type) {

	this->size = new b2Vec2(width, height);

	b2PolygonShape box_shape;
	box_shape.SetAsBox(width/2,height/2); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;
	body_fixture.density = density;
	body_fixture.friction = friction;

	b2BodyDef body_definition;
	body_definition.angle = angle;

	if(body_type == Polygon::STATIC){
		body_definition.type = b2_staticBody;
	} else {
		body_definition.type = b2_dynamicBody;
	}

	body_definition.position.Set(posX, posY); //seteo posicion base

	Polygon::create_body(&body_definition, &body_fixture, world);

	//Lo necesario para SDL!

	this->addB2DPoint(-width/2, height/2);
	this->addB2DPoint(width/2, height/2);
	this->addB2DPoint(width/2, -height/2);
	this->addB2DPoint(-width/2, -height/2);

	this->createSDLPoints();
}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

