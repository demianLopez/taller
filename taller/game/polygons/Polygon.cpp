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

Polygon::Polygon(int body_def) {

	this->body_def = body_def;
	this->body = NULL;
	this->world = NULL;

	this->polygonImage = NULL;

	this->r = 0;
	this->b = 0;
	this->g = 0;
}



void Polygon::setColor(int r, int g, int b){
	this->r = r;
	this->g = g;
	this->b = b;

	this->createSDLPoints();
}

b2Body * Polygon::getBody(){
	return body;
}

void Polygon::addB2DPoint(double x, double y){
	this->pointList.push_back(new b2Vec2(x, y));
}

void Polygon::createSDLPoints(){

	//Buscamos el ancho y largo maximo!!
	double xMaxPos = 0;
	double xMaxNeg = 0;
	double yMaxPos = 0;
	double yMaxNeg = 0;

	for(auto *point : pointList){
		if(point->x < 0){
			if(point->x < xMaxNeg){
				xMaxNeg = point->x;
			}
		} else {
			if(point->x > xMaxPos){
				xMaxPos = point->x;
			}
		}

		if(point->y < 0){
			if(point->y < yMaxNeg){
				yMaxNeg = point->y;
			}
		} else {
			if(point->y > yMaxPos){
				yMaxPos = point->y;
			}
		}
	}

	b2Vec2 b2DSize = b2Vec2(xMaxPos - xMaxNeg, yMaxPos - yMaxNeg);

	if(this->polygonImage != NULL){
		delete this->polygonImage;
	}

	short int * vX;
	short int * vY;
	short int pointSize = pointList.size();

	vX = new short int[pointSize];
	vY = new short int[pointSize];

	short int c = 0;
	b2Vec2 sdlSize = this->world->box2DToSDLSize(&b2DSize);

	if(((int) sdlSize.x)%2 == 0){
		sdlSize.x++;
	}

	if(((int) sdlSize.y%2) == 0){
		sdlSize.y++;
	}

	int centerX = sdlSize.x / 2;
	int centerY = sdlSize.y / 2;

	for(auto *point : pointList){
		b2Vec2 sdlPos = this->world->box2DToSDLSize(point);
		vX[c] = sdlPos.x + centerX;
		vY[c] = sdlSize.y - (sdlPos.y + centerY);
		c++;
	}

	this->polygonImage = new Image(sdlSize.x, sdlSize.y);
	Graphics * g = this->polygonImage->getGraphics();
	SDL_SetRenderTarget(GameElements::gRenderer, this->polygonImage->getImageTexture());
	g->drawFillPolygon(vX, vY, pointSize, this->r, this->g, this->b);

	delete[] vX;
	delete[] vY;
}

Polygon::~Polygon() {
	for(auto *point : pointList){
		delete point;
	}
	pointList.clear();

	if(this->polygonImage != NULL){

		delete this->polygonImage;
	}
}

void Polygon::render(Graphics * g){
	b2Vec2 b2DPos = this->body->GetPosition();
	b2Vec2 sdlPos = this->world->box2DToSDL(&b2DPos);

	g->drawAtCenter(true);
	g->drawImage(this->polygonImage, sdlPos.x, sdlPos.y,  - this->body->GetAngle() * 57.2957);
	g->drawAtCenter(false);
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