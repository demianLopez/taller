/*
 * BonusEntity.cpp
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#include "BonusEntity.h"
#include "../../common/UpdateRequest.h"
#include "../engine/Graphics.h"
#include "../GameWorld.h"
#include "../Global.h"
#include "../Resources.h"
#include "../VectorXY.h"

BonusEntity::BonusEntity(int index) : GameEntity(index) {
	// TODO Auto-generated constructor stub

}

void BonusEntity::render(Graphics* g, unsigned int dela) {
	g->drawAtCenter(true);
	VectorXY b2DPos = VectorXY(posX, posY);
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&b2DPos);
	g->drawImage(Global::gameResources->getBonusByType(type), sdlPos.x, sdlPos.y);
	g->drawAtCenter(false);
}

void BonusEntity::update(unsigned int delta) {
}

void BonusEntity::addUpdateRequest(UpdateRequest* u, unsigned int currentTime) {
}

void BonusEntity::initialize() {
}


void BonusEntity::putAt(float posX, float posY, int bonusType) {
	this->posX = posX;
	this->posY = posY;
	this->type = bonusType;
	this->active = true;
}

BonusEntity::~BonusEntity() {
	// TODO Auto-generated destructor stub
}

