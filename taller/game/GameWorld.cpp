/*
 * GameWorld.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "GameWorld.h"
#include "entity/GameEntity.h"
#include "Global.h"

/* Crea un GameWorld.
 * Recibe el tamanyo del mundo de box2d. */
GameWorld::GameWorld(float tX, float tY) {
	this->box2DSize = VectorXY(tX, tY);
	this->sdlWorldSize = VectorXY(tX * 20, tY * 20);
	this->mainEntity = NULL;
}

GameEntity * GameWorld::getMainEntity(){
	return this->mainEntity;
}

/* Setea tamanyo de la pantalla. */
void GameWorld::setScreenSize(VectorXY screenSize){
	this->screenSize = screenSize;
}

/* Devuelve el tamanyo del mundo de box2d. */
VectorXY GameWorld::getBox2DWorldSize(){
	return this->box2DSize;
}


void GameWorld::setMainEntity(int index){
	this->mainEntity = this->searchEntity(index);
}

GameEntity * GameWorld::searchEntity(int index){
	for(auto * e : entityList){
		if(e->getIndex() == index){
			return e;
		}
	}

	return NULL;
}

/* Agrega un GameEntity. */
void GameWorld::addEntity(GameEntity * entity){
	this->updateMutex.lock();
	this->entityList.push_back(entity);
	this->updateMutex.unlock();
}

/* Realiza los updates. */
void GameWorld::update(){
	this->updateMutex.lock();
	for(auto * update : this->updatesList){
		for(auto * entity : this->entityList){
			if(entity->getIndex() == update->index){
				entity->update(update);
				break;
			}
		}

		delete update;
	}

	this->updatesList.clear();
	this->updateMutex.unlock();
}

/* Agrega pedido de request. */
void GameWorld::addUpdateRequest(UpdateRequest * update){
	this->updateMutex.lock();
	this->updatesList.push_back(update);
	this->updateMutex.unlock();
}

/* Devuelve entityList. */
std::vector<GameEntity*> GameWorld::getEntityList(){
	return this->entityList;
}

/* Inicializa los componentes graficos. */
void GameWorld::generateGraphics(){
	for(auto * e : entityList){
		e->setWorld(this);
		e->initialize();
	}
}

VectorXY GameWorld::box2DToSDLSize(VectorXY * box2DCoord){
	int screenW = this->sdlWorldSize.x;
	int screenH = this->sdlWorldSize.y;

	float sdlX = box2DCoord->x / box2DSize.x * screenW;
	float sdlY = box2DCoord->y / box2DSize.y * screenH;
	VectorXY sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

VectorXY GameWorld::getSdlWorldSize(){
	return this->sdlWorldSize;
}

VectorXY GameWorld::box2DToSDL(VectorXY * box2DCoord){
	int screenW = this->sdlWorldSize.x;
	int screenH = this->sdlWorldSize.y;

	float sdlX = box2DCoord->x / box2DSize.x * screenW;
	float sdlY = screenH
			- box2DCoord->y / box2DSize.y * screenH;
	VectorXY sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

GameWorld::~GameWorld() {
	for(auto * e : entityList){
		delete e;
	}
}

