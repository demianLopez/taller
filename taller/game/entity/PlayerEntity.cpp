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
	this->position = VectorXY(u->posX, u->posY);
	this->animation = u->animation;
}

void PlayerEntity::initialize(){

}

void PlayerEntity::render(Graphics * g){
	g->drawAtCenter(true);
	VectorXY sdlPos = Global::gameWorld->box2DToSDL(&position);
	g->drawAnimation(Global::gameResources->getPlayerAnimationLeft(), sdlPos.x, sdlPos.y);
	g->drawAtCenter(false);
}

void PlayerEntity::setAnimation(int animation){
	this->animation = animation;
}

PlayerEntity::~PlayerEntity() {
	// TODO Auto-generated destructor stub
}

