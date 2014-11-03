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

void PlayerEntity::update(UpdateRequest * u){
	this->lastPosition = this->position;
	this->position = VectorXY(u->posX, u->posY);
	this->animation = u->animation;

	int currentTime = Global::game->getElapsedTime();
	this->elapsedTime = currentTime - this->lastUpdateTime;
	this->lastUpdateTime = currentTime;

}

void PlayerEntity::initialize(){

}

void PlayerEntity::render(Graphics * g){
	g->drawAtCenter(true);

	int renderTime = Global::game->getElapsedTime() - this->lastUpdateTime;
	float d = (float)(renderTime)/(float) (elapsedTime);

	if(d > 1) { d = 1; }
	float iPosX = lastPosition.x + (position.x - lastPosition.x) * d;
	float iPosY = lastPosition.y + (position.y - lastPosition.y) * d;


	interpolatedPosition = VectorXY(iPosX, iPosY);
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&interpolatedPosition);

	g->drawAnimation(Global::gameResources->getPlayerAnimationLeft(), sdlPos.x, sdlPos.y);
	g->drawAtCenter(false);
}

void PlayerEntity::setAnimation(int animation){
	this->animation = animation;
}

PlayerEntity::~PlayerEntity() {
	// TODO Auto-generated destructor stub
}

