/*
 * GameWorld.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "GameWorld.h"
#include "entity/GameEntity.h"

/* Crea un GameWorld.
 * Recibe el tamanyo del mundo de box2d. */
GameWorld::GameWorld(float tX, float tY) {
	this->box2DSize = VectorXY(tX, tY);
}

/* Setea tamanyo de la pantalla. */
void GameWorld::setScreenSize(VectorXY screenSize){
	this->screenSize = screenSize;
}

/* Devuelve el tamanyo del mundo de box2d. */
VectorXY GameWorld::getBox2DWorldSize(){
	return this->box2DSize;
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
	this->updatesList.push_back(update);
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
	float sdlX = box2DCoord->x / box2DSize.x * 800;
	float sdlY = box2DCoord->y / box2DSize.y * 600;
	VectorXY sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

VectorXY GameWorld::box2DToSDL(VectorXY * box2DCoord){
	float sdlX = box2DCoord->x / box2DSize.x * 800;
	float sdlY = 600
			- box2DCoord->y / box2DSize.y * 600;
	VectorXY sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

GameWorld::~GameWorld() {
	for(auto * e : entityList){
		delete e;
	}
}

