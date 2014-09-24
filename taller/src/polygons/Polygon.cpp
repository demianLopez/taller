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
#include <math.h>

#include <Box2D/Box2D.h>

Polygon::Polygon(int body_def) {

	this->body_def = body_def;
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

	float rotation = this->body->GetAngle();

	float sinAngle = sin(rotation);
	float cosAngle = cos(rotation);

	this->pointSize = pointList.size();

	if(this->vX == NULL){
		vX = new short int[pointSize];
	}

	if(this->vY == NULL){
		vY = new short int[pointSize];
	}

	short int c = 0;

	b2Vec2 polPos = this->body->GetPosition();

	b2Vec2 SDLTranslation = this->world->box2DToSDL(&polPos);

	for(auto *point : pointList){
		b2Vec2 rotatedPoint = b2Vec2(point->x * cosAngle - point->y * sinAngle,
				point->x * sinAngle + point->y * cosAngle);
		b2Vec2 sdlPos = this->world->box2DToSDL(&rotatedPoint);
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
	if(!this->shouldIRender()){
		return; //Evitamos gastar recursos renderizando algo que no esta en pantalla
	}

	if(this->body_def == Polygon::DYNAMIC){
		this->createSDLPoints();
	}

	if(pointSize != 0){
		g->drawFillPolygon(vX, vY, pointSize, this->r, this->g, this->b);
	}
}

bool Polygon::shouldIRender(){
	return !this->world->isOutOfWorld(this->body->GetPosition());
}

b2Vec2 * Polygon::getPosition(){
	return (b2Vec2*)&this->body->GetPosition();
}

void Polygon::create_body(b2BodyDef* body_definition,
		b2FixtureDef* body_fixture,  World * world) {
	this->world = world;
	b2World * bWorld = world->getBox2DWorld();
	this->body = bWorld->CreateBody(body_definition);
	b2Fixture *fixture = this->body->CreateFixture(body_fixture);

	fixture->SetUserData( (void*) 1); // Le ponemos a los poligonos el tag "1". (Para detectar colisiones)

	this->body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
}
