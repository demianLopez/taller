/*
 * ProjectileEntity.cpp
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#include "ProjectileEntity.h"
#include "../../common/UpdateRequest.h"
#include "../engine/Graphics.h"
#include "../GameWorld.h"
#include "../Global.h"
#include "../Resources.h"
#include "../VectorXY.h"

ProjectileEntity::ProjectileEntity(int index) : MovementEntity(index) {
	// TODO Auto-generated constructor stub

}

void ProjectileEntity::render(Graphics* g, unsigned int delta) {
	g->drawAtCenter(true);
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);
	g->drawAnimation(
		Global::gameResources->getSleepingEmoticon(),
		sdlPos.x, sdlPos.y);
	g->drawAtCenter(false);
}

void ProjectileEntity::initialize() {
}

void ProjectileEntity::applyUpdate(UpdateRequest* u) {

}

ProjectileEntity::~ProjectileEntity() {
	// TODO Auto-generated destructor stub
}

