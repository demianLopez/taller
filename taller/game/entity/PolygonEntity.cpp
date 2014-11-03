/*
 * PolygonEntity.cpp
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */


#include "PolygonEntity.h"
#include <Global.h>

PolygonEntity::PolygonEntity(int index) : GameEntity(index) {
	this->polygonImage = NULL;
}

void PolygonEntity::update(UpdateRequest * u){
	this->lastPosition = this->position;
	this->position = VectorXY(u->posX, u->posY);

	this->interpolatedPosition = this->lastPosition;

	this->lastRotation = this->rotation;
	this->rotation = u->rotation;

	int currentTime = Global::game->getElapsedTime();
	this->elapsedTime = currentTime - this->lastUpdateTime;
	this->lastUpdateTime = currentTime;
}

void PolygonEntity::setStatic(bool isStatic){
	this->isStatic = isStatic;
}

void PolygonEntity::render(Graphics * g){

	if(this->polygonImage == NULL){
		return;
	}

	VectorXY sdlPos;
	float finalRotation;

	if(!this->isStatic){
		int renderTime = Global::game->getElapsedTime() - this->lastUpdateTime;
		float d = (float)(renderTime)/(float) (elapsedTime);

		if(d > 1) { d = 1; }
		float iPosX = lastPosition.x + (position.x - lastPosition.x) * d;
		float iPosY = lastPosition.y + (position.y - lastPosition.y) * d;
		finalRotation = lastRotation + (rotation - lastRotation) * d;

		interpolatedPosition = VectorXY(iPosX, iPosY);
		sdlPos = this->gameWorld->box2DToSDL(&interpolatedPosition);
	} else {
		interpolatedPosition = position;
		lastPosition = position;
		sdlPos = this->gameWorld->box2DToSDL(&position);
		finalRotation = rotation;
	}

	g->drawAtCenter(true);
	g->drawImage(this->polygonImage, sdlPos.x, sdlPos.y, -finalRotation * 57);
	g->drawAtCenter(false);
}

void PolygonEntity::initialize(){
	//Buscamos el ancho y largo maximo!!

	if(this->vList.size() < 3){
		return;
	}

	double xMaxPos = 0;
	double xMaxNeg = 0;
	double yMaxPos = 0;
	double yMaxNeg = 0;

	for (auto *point : vList) {
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

	VectorXY b2DSize = VectorXY(xMaxPos - xMaxNeg, yMaxPos - yMaxNeg);

	if (this->polygonImage != NULL) {
		delete this->polygonImage;
	}

	short int * vX;
	short int * vY;
	short int pointSize = vList.size();

	vX = new short int[pointSize];
	vY = new short int[pointSize];

	short int c = 0;
	VectorXY sdlSize = this->gameWorld->box2DToSDLSize(&b2DSize);
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

	for (auto *point : vList) {
		VectorXY sdlPos = this->gameWorld->box2DToSDLSize(point);
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
	g->drawFillPolygon(vX, vY, pointSize, 0, 255, 0);

	delete[] vX;
	delete[] vY;
	delete g;
	delete borderImage;
}

void PolygonEntity::addVertex(float x, float y){
	this->vList.push_back(new VectorXY(x, y));
}

PolygonEntity::~PolygonEntity() {
	for(auto * v : vList){
		delete v;
	}

	if(polygonImage != NULL){
		delete this->polygonImage;
	}
}


