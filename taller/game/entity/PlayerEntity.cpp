/*
 * PlayerEntity.cpp
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#include "PlayerEntity.h"
#include <Global.h>

PlayerEntity::PlayerEntity(int index) :
		GameEntity(index) {
	// TODO Auto-generated constructor stub
	this->renderTimeCount = 0;
	this->lName = 0;

	firstUpdate = false;
}

void PlayerEntity::setPlayerName(char * name) {
	this->pName = name;
	this->lName = strlen(name);
}

void PlayerEntity::update(unsigned int delta) {
	if (!this->firstUpdate) {
		return;
	}

	this->renderTimeCount += delta;
	UpdateRequest * u = NULL;

	if (renderTimeCount > this->updateTime.front()) {
		if (updateRequest.size() <= 1) {
			this->renderTimeCount = this->updateTime.front();
			return;
		}

		renderTimeCount -= this->updateTime.front();

		u = updateRequest.front();
		updateRequest.pop();
		updateTime.pop();
		delete u;

		u = this->updateRequest.front();

		this->lastPosition = this->nextPosition;
		this->nextPosition = VectorXY(u->posX, u->posY);

		this->animation = u->animation;
		this->offline = u->offline;
	}

	float d = (float) (renderTimeCount)
			/ (float) (updateTime.front());

	if (d > 1) {
		d = 1;
	}
	float iPosX = lastPosition.x + (nextPosition.x - lastPosition.x) * d;
	float iPosY = lastPosition.y + (nextPosition.y - lastPosition.y) * d;

	position = VectorXY(iPosX, iPosY);
}

void PlayerEntity::addUpdateRequest(UpdateRequest * u,
		unsigned int elapsedTime) {

	unsigned int difTime = elapsedTime - this->lastUpdateTime;
	this->lastUpdateTime = elapsedTime;

	this->updateTime.push(difTime);
	this->updateRequest.push(u);

	if (!firstUpdate && (updateTime.size() > 1)) {
		this->lastPosition = VectorXY(updateRequest.front()->posX,
				updateRequest.front()->posY);
		this->nextPosition = VectorXY(u->posX, u->posY);
		updateRequest.pop();
		updateTime.pop();
		this->firstUpdate = true;
	}
}

void PlayerEntity::setOffline(bool offline) {
	this->offline = offline;
}

void PlayerEntity::initialize() {

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

	while(updateRequest.size() > 0){
		delete updateRequest.front();
		updateRequest.pop();
	}
}

