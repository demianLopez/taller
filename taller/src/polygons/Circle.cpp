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

Circle::Circle(double diameter, double posX, double posY, double density, int body_type,
		World * world) :
		Polygon(body_type) {

	b2CircleShape circle_shape;
	circle_shape.m_p.Set(0, 0);

	float32 radius = diameter/2;
	circle_shape.m_radius = radius;

	b2FixtureDef body_fixture;
	body_fixture.shape = &circle_shape;

	b2BodyDef body_definition;
	body_definition.position.Set(posX, posY); //seteo posicion base

	Polygon::create_body(&body_definition, &body_fixture, world);

	this->circleImage = new Image("Resources/bola.png");
}

void Circle::render(Graphics * g){
	b2Vec2 pos = this->body->GetPosition();
	b2Vec2 SDLPos = this->world->box2DToSDL(&pos);

	g->drawImage(this->circleImage, SDLPos.x, SDLPos.y, this->body->GetAngle() * 360);

}
