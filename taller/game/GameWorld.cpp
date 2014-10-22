/*
 * GameWorld.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "GameWorld.h"

GameWorld::GameWorld(VectorXY box2DWorldSize) {
	this->box2DSize = box2DWorldSize;
}

void GameWorld::setScreenSize(VectorXY screenSize){
	this->screenSize = screenSize;
}

VectorXY GameWorld::getBox2DWorldSize(){
	return this->box2DSize;
}

std::vector<Polygon*> GameWorld::getPolygonList(){
	return this->polygonList;
}

GameWorld::~GameWorld() {
	// TODO Auto-generated destructor stub
}

