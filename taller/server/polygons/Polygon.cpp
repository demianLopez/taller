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
#include <math.h>
#include "../ContactContainer.h"

Polygon::Polygon(int body_def) {

	this->type = P_SOLID;
	this->body_def = body_def;
	this->body = NULL;
	this->world = NULL;

	this->tipoDeObjeto = 1; // Para los contactos. Los poligonos tienen valor 1.
}

b2Body * Polygon::getBody() {
	return body;
}

void Polygon::addB2DPoint(double x, double y) {
	this->pointList.push_back(new b2Vec2(x, y));
}

vector<b2Vec2 *> Polygon::getPointList() {
	return this->pointList;
}

void Polygon::setEntityIndex(int index) {
	this->entityIndex = index;
}

int Polygon::getEntityIndex() {
	return entityIndex;
}

/*
 void Polygon::createSDLPoints() {


 //Buscamos el ancho y largo maximo!!
 double xMaxPos = 0;
 double xMaxNeg = 0;
 double yMaxPos = 0;
 double yMaxNeg = 0;

 for (auto *point : pointList) {
 if (point->x < 0) {
 if (point->x < xMaxNeg) {
 xMaxNeg = point->x;
 }
 } else {
 if (point->x > xMaxPos) {
 xMaxPos = point->x;
 }
 }

 if (point->y < 0) {
 if (point->y < yMaxNeg) {
 yMaxNeg = point->y;
 }
 } else {
 if (point->y > yMaxPos) {
 yMaxPos = point->y;
 }
 }
 }

 b2Vec2 b2DSize = b2Vec2(xMaxPos - xMaxNeg, yMaxPos - yMaxNeg);

 if (this->polygonImage != NULL) {
 delete this->polygonImage;
 }

 short int * vX;
 short int * vY;
 short int pointSize = pointList.size();

 vX = new short int[pointSize];
 vY = new short int[pointSize];

 short int c = 0;
 b2Vec2 sdlSize = this->world->box2DToSDLSize(&b2DSize);
 sdlSize.x *= 1.5;
 sdlSize.y *= 1.5;

 if (((int) sdlSize.x) % 2 == 0) {
 sdlSize.x++;
 }

 if (((int) sdlSize.y % 2) == 0) {
 sdlSize.y++;
 }

 int centerX = sdlSize.x / 2;
 int centerY = sdlSize.y / 2;

 for (auto *point : pointList) {
 b2Vec2 sdlPos = this->world->box2DToSDLSize(point);
 vX[c] = sdlPos.x + centerX;
 vY[c] = sdlSize.y - (sdlPos.y + centerY);
 c++;
 }

 this->polygonImage = new Image(sdlSize.x, sdlSize.y);
 Image * borderImage = new Image("Resources/border.png");
 Graphics * g = GameElements::getGraphicsInstance();
 g->setColor(0, 0, 0, 0);
 g->setRendererObject(this->polygonImage);
 g->clearRenderObject();
 g->drawFillPolygon(vX, vY, pointSize, this->r, this->g, this->b);

 delete[] vX;
 delete[] vY;
 delete g;
 delete borderImage;

 }
 */

Polygon::~Polygon() {
	for (auto *point : pointList) {
		delete point;
	}
	pointList.clear();
}

float Polygon::getRotation() {
	return this->body->GetAngle();
}
/*
 void Polygon::render(Graphics * g) {

 b2Vec2 b2DPos = this->body->GetPosition();
 b2Vec2 sdlPos = this->world->box2DToSDL(&b2DPos);

 g->drawAtCenter(true);
 g->drawImage(this->polygonImage, sdlPos.x, sdlPos.y,
 -this->body->GetAngle() * 57.2957);
 g->drawAtCenter(false);

 }
 */

EntityType Polygon::getType() {
	return this->type;
}

bool Polygon::isStatic() {
	return body->GetType() == b2_staticBody;
}

b2Vec2 * Polygon::getPosition() {
	return (b2Vec2*) &this->body->GetPosition();
}

void Polygon::create_body(b2BodyDef* body_definition,
		b2FixtureDef* body_fixture, World * world) {
	this->world = world;
	b2World * bWorld = world->getBox2DWorld();
	this->body = bWorld->CreateBody(body_definition);
	b2Fixture *fixture = this->body->CreateFixture(body_fixture);

	fixture->SetUserData(new ContactContainer(ContactContainer::POLYGON, this)); // Para detectar colisiones.

	this->body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
}
