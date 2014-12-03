/*
 * PlayerEntity.cpp
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#include "PlayerEntity.h"

#include <cstring>

#include "../../common/UpdateRequest.h"
#include "../engine/Graphics.h"
#include "../GameWorld.h"
#include "../Global.h"
#include "../Resources.h"
#include "../VectorXY.h"

PlayerEntity::PlayerEntity(int index) :
		MovementEntity(index) {

	this->lName = 0;
	this->invulnerable = false;
	this->offline = false; // Por defecto lo seteo en false
	this->blinkingTime = 1; //idem
	this->pName = NULL;
}

/* Recibe name con memoria ya alocada. Se encarga de liberarla. */
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
	this->invulnerable = u->invulnerable;
}

void PlayerEntity::render(Graphics * g, unsigned int delta) {

	//int renderTime = Global::game->getElapsedTime() - this->lastUpdateTime;

	this->blinkingTime += delta;
	this->blinkingTime = blinkingTime % 500;

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
		if(!(invulnerable && blinkingTime > 250)){
			g->drawAnimation(
				Global::gameResources->getAnimationByAnimationCode(animation),
				sdlPos.x, sdlPos.y);
		}
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

PlayerEntity::~PlayerEntity() {
	if(this->pName) delete[] this->pName;
}

