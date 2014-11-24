/*
 * MovementEntity.cpp
 *
 *  Created on: 23/11/2014
 *      Author: demian
 */

#include "MovementEntity.h"

#include <stddef.h>


MovementEntity::MovementEntity(int index) : GameEntity(index) {
	this->renderTimeCount = 0;
	this->nextRotation = 0;
	this->lastRotation = 0;
	this->lastUpdateTime = 0;
	firstUpdate = false;
}

void MovementEntity::update(unsigned int delta) {
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

		this->lastRotation = this->nextRotation;
		this->nextRotation = u->rotation;

		this->applyUpdate(u);
	}

	float d = (float) (renderTimeCount)
			/ (float) (updateTime.front());

	if (d > 1) {
		d = 1;
	}
	float iPosX = lastPosition.x + (nextPosition.x - lastPosition.x) * d;
	float iPosY = lastPosition.y + (nextPosition.y - lastPosition.y) * d;


	this->rotation = lastRotation + (nextRotation - lastRotation) * d;
	position = VectorXY(iPosX, iPosY);
}

void MovementEntity::addUpdateRequest(UpdateRequest * u,
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

MovementEntity::~MovementEntity() {
	while(updateRequest.size() > 0){
		delete updateRequest.front();
		updateRequest.pop();
	}
}

