/*
 * PlayerEntity.cpp
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#include "PlayerEntity.h"
#include <Global.h>

PlayerEntity::PlayerEntity(int index) : GameEntity(index) {
	// TODO Auto-generated constructor stub

}

void PlayerEntity::setPlayerName(char * name){
	this->pName = name;
	this->lName = strlen(name);
}

void PlayerEntity::update(UpdateRequest * u,  unsigned int elapsedTime){
	this->lastPosition = this->nextPosition;
	this->nextPosition = VectorXY(u->posX, u->posY);

	this->animation = u->animation;
	this->offline = u->offline;

	int currentTime = Global::game->getElapsedTime();
	this->elapsedTime = currentTime - this->lastUpdateTime;
	this->lastUpdateTime = currentTime;
	this->renderTimeCount = 0;
}

void PlayerEntity::setOffline(bool offline){
	this->offline = offline;
}

void PlayerEntity::initialize(){

}

void PlayerEntity::render(Graphics * g, unsigned int delta){


	//int renderTime = Global::game->getElapsedTime() - this->lastUpdateTime;
	this->renderTimeCount+= delta;
	float d = (float)(renderTimeCount)/(float) (elapsedTime);

	if(d > 1) { d = 1; }
	float iPosX = lastPosition.x + (nextPosition.x - lastPosition.x) * d;
	float iPosY = lastPosition.y + (nextPosition.y - lastPosition.y) * d;


	position = VectorXY(iPosX, iPosY);
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);


	//VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);
	g->drawAtCenter(true);
	if(offline){
		g->drawAnimation(Global::gameResources->getSleepingEmoticon(), sdlPos.x + 10, sdlPos.y - 50);
	}
	g->drawAnimation(Global::gameResources->getAnimationByAnimationCode(animation), sdlPos.x, sdlPos.y);
	g->setFont(Global::gameResources->getNameFont());

	g->setColor(0, 0, 0);

	if(!offline){
		g->drawText(sdlPos.x - this->lName * 5, sdlPos.y - 60, this->pName);
	}

	g->drawAtCenter(false);
}

void PlayerEntity::setAnimation(AnimationCode animation){
	this->animation = animation;
}

PlayerEntity::~PlayerEntity() {
	delete this->pName;
}

