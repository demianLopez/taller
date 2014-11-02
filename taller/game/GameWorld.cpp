/*
 * GameWorld.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "GameWorld.h"

GameWorld::GameWorld(float tX, float tY) {
	this->box2DSize = VectorXY(tX, tY);
}

void GameWorld::setScreenSize(VectorXY screenSize){
	this->screenSize = screenSize;
}

VectorXY GameWorld::getBox2DWorldSize(){
	return this->box2DSize;
}

void GameWorld::addEntity(GameEntity * entity){
	this->entityList.push_back(entity);
}

std::vector<GameEntity*> GameWorld::getEntityList(){
	return this->entityList;
}

void GameWorld::generateGraphics(){

}

GameWorld::~GameWorld() {

}

