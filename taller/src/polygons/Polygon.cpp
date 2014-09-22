/**
 Polygon.cpp

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
#include "Polygon.h"

#include <Box2D/Box2D.h>

Polygon::Polygon(int body_type) {
	if (body_type == STATIC) {
		this->body_type = b2_staticBody;
	} else { //Por defecto es dinamico (body_type == DYNAMIC)
		this->body_type = b2_dynamicBody;
	}

	this->body = NULL;
	this->vX = NULL;
	this->vY = NULL;
	this->world = NULL;

	this->pointSize = 0;

	this->r = 0;
	this->b = 0;
	this->g = 0;
}

void Polygon::setColor(int r, int g, int b){
	this->r = r;
	this->g = g;
	this->b = b;
}

void Polygon::addB2DPoint(double x, double y){
	this->pointList.push_back(new b2Vec2(x, y));
}

void Polygon::createSDLPoints(){

	//float rotation = this->body->GetAngle();

	if(this->vX != NULL){
		delete[] vX;
	}

	if(this->vY != NULL){
		delete[] vY;
	}

	this->pointSize = pointList.size();
	vX = new short int[pointSize];
	vY = new short int[pointSize];

	short int c = 0;

	b2Vec2 polPos = this->body->GetPosition();
	b2Vec2 SDLTranslation = this->world->box2DToSDL(&polPos);

	for(auto *point : pointList){
		b2Vec2 sdlPos = this->world->box2DToSDL(point);
		vX[c] = sdlPos.x + SDLTranslation.x;
		vY[c] = sdlPos.y + SDLTranslation.y - this->world->getWindowSize()->y;

		c++;
	}
}

Polygon::~Polygon() {
	if(this->vX != NULL){
		delete[] vX;
	}

	if(this->vY != NULL){
		delete[] vY;
	}

	for(auto *point : pointList){
		delete point;
	}

	pointList.clear();
}

void Polygon::render(Graphics * g){
	if(pointSize != 0){
		g->drawFillPolygon(vX, vY, pointSize, this->r, this->g, this->b);
	}
}

b2Vec2 * Polygon::getPosition(){
	return (b2Vec2*)&this->body->GetPosition();
}

void Polygon::create_body(b2BodyDef* body_definition,
		b2FixtureDef* body_fixture,  World * world) {
	this->world = world;
	b2World * bWorld = world->getBox2DWorld();
	this->body = bWorld->CreateBody(body_definition);
	this->body->CreateFixture(body_fixture);

	this->body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
}
