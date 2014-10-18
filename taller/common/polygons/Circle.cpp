/**
 Circle.cpp

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
#include "Circle.h"

Circle::~Circle() {
	delete this->circleImage;
}

Circle::Circle(double diameter, double posX, double posY, double density,
		double angle, int body_type, World * world) :
		Polygon(body_type) {

	b2CircleShape circle_shape;
	//circle_shape.m_p.Set(0, 0);
	this->diameter = diameter;
	float32 radius = diameter / 2;
	circle_shape.m_radius = radius;

	b2FixtureDef body_fixture;
	body_fixture.shape = &circle_shape;
	body_fixture.density = density;
	body_fixture.friction = friction;

	b2BodyDef body_definition;
	body_definition.angle = angle;

	if (body_type == Polygon::STATIC) {
		body_definition.type = b2_staticBody;
	} else {
		body_definition.type = b2_dynamicBody;
	}

	body_definition.position.Set(posX, posY); //seteo posicion base

	Polygon::create_body(&body_definition, &body_fixture, world);

	this->circleImage = new Image("Resources/bola.png");
}

void Circle::render(Graphics * g) {
	if (!this->shouldIRender()) {
		return; //Evitamos gastar recursos renderizando algo que no esta en pantalla
	}

	b2Vec2 pos = this->body->GetPosition();
	b2Vec2 SDLPos = this->world->box2DToSDL(&pos);

	b2Vec2 size = b2Vec2(this->diameter, this->diameter);
	b2Vec2 SDLsize = this->world->box2DToSDL(&size);

	g->drawAtCenter(true);
	g->drawImage(this->circleImage, SDLPos.x, SDLPos.y, SDLsize.x,
			SDLsize.y - this->world->getWindowSize()->y,
			-this->body->GetAngle() * 57);
	g->drawAtCenter(false);
}
