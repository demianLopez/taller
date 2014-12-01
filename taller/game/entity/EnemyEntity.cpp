/*
 * EnemyEntity.cpp
 *
 *  Created on: 29/11/2014
 *      Author: demian
 */

#include "EnemyEntity.h"
#include "../../common/UpdateRequest.h"
#include "../engine/Graphics.h"
#include "../GameWorld.h"
#include "../Global.h"
#include "../Resources.h"
#include "../VectorXY.h"

EnemyEntity::EnemyEntity(int index) : MovementEntity(index) {
	// TODO Auto-generated constructor stub

}

void EnemyEntity::render(Graphics* g, unsigned int delta) {
	g->drawAtCenter(true);
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);
	g->drawAnimation(
		Global::gameResources->getBossAnimationLeft(),
		sdlPos.x, sdlPos.y);
	g->drawAtCenter(false);
}

void EnemyEntity::initialize() {
}

void EnemyEntity::applyUpdate(UpdateRequest* u) {
	this->animation = u->animation;
}

EnemyEntity::~EnemyEntity() {
	// TODO Auto-generated destructor stub
}

