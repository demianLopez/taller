/*
 * PlayerEntity.cpp
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#include "PlayerEntity.h"
#include <Global.h>

PlayerEntity::PlayerEntity(int index) :
		MovementEntity(index) {
	// TODO Auto-generated constructor stub

	this->lName = 0;


}

void PlayerEntity::setPlayerName(char * name) {
	this->pName = name;
	this->lName = strlen(name);
}


void PlayerEntity::setOffline(bool offline) {
	this->offline = offline;
}

void PlayerEntity::initialize() {

}

void PlayerEntity::applyUpdate(UpdateRequest * u){
	this->animation = u->animation;
	this->offline = u->offline;
}

void PlayerEntity::render(Graphics * g, unsigned int delta) {

	//int renderTime = Global::game->getElapsedTime() - this->lastUpdateTime;

	VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);

	//VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);
	g->drawAtCenter(true);
	if (offline) {
		g->drawAnimation(Global::gameResources->getSleepingEmoticon(),
				sdlPos.x + 10, sdlPos.y - 50);
		g->drawAnimation(
				Global::gameResources->getAnimationByAnimationCode(animation,
						true), sdlPos.x, sdlPos.y);
	} else {
		g->drawAnimation(
				Global::gameResources->getAnimationByAnimationCode(animation),
				sdlPos.x, sdlPos.y);
	}
	g->setFont(Global::gameResources->getNameFont());

	if (!offline) {
		g->setColor(0, 0, 0, 150);
		g->drawFillRect(sdlPos.x - this->lName * 5 - 7, sdlPos.y - 56,
				this->lName * 10 + 20, 20);
		g->setColor(255, 255, 255);
		g->drawText(sdlPos.x - this->lName * 5, sdlPos.y - 60, this->pName);
	}

	g->drawAtCenter(false);
}

void PlayerEntity::setAnimation(AnimationCode animation) {
	this->animation = animation;
}

PlayerEntity::~PlayerEntity() {
	delete this->pName;
}

