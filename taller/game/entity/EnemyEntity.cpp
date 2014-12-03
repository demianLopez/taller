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

EnemyEntity::EnemyEntity(int index, int type) : MovementEntity(index) {
	this->type = type;
}

void EnemyEntity::render(Graphics* g, unsigned int delta) {
	g->drawAtCenter(true);
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);
	if(animation != SNOW_LEVEL_4){
		if(type == 2){
		g->drawAnimation(
				Global::gameResources->getEnemy2AnimationByCode(this->animation),
				sdlPos.x, sdlPos.y);
		} else {
			g->drawAnimation(
					Global::gameResources->getEnemyAnimationByCode(this->animation),
					sdlPos.x, sdlPos.y);
		}
	}
	Image * snowBall = Global::gameResources->getSnowBalLevel(animation);
	if(snowBall != NULL){
		g->drawImage(snowBall, sdlPos.x, sdlPos.y, -57 * rotation);
	}
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

