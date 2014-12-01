/*
 * GameEntity.cpp
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#include "GameEntity.h"

GameEntity::GameEntity(int index) {
	this->entityIndex = index;
	this->rotation = 0;
	this->position = VectorXY(0, 0);
	this->gameWorld = nullptr;
	this->type = 0;
	this->active = true;
}

void GameEntity::setActive(bool active){
	this->active = active;
	this->setedActive(active);
}

bool GameEntity::isActive(){
	return this->active;
}

VectorXY GameEntity::getPosition() {
	return this->position;
}

int GameEntity::getIndex() {
	return entityIndex;
}

void GameEntity::setType(EntityType type) {
	this->type = type;
}

void GameEntity::setPosition(float x, float y) {
	this->position = VectorXY(x, y);
}

void GameEntity::setRotation(float rotation) {
	this->rotation = rotation;

}

void GameEntity::setWorld(GameWorld * gameWorld) {
	this->gameWorld = gameWorld;
}

GameEntity::~GameEntity() {
}

