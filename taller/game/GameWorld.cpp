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

void GameWorld::setWaitingForPlayers(bool waitingForPlayers){
	this->waitingForPlayers = waitingForPlayers;
}

bool GameWorld::isWaitingForPlayers(){
	return this->waitingForPlayers;
}

GameEntity * GameWorld::getMainEntity() {
	return this->mainEntity;
}

/* Setea tamanyo de la pantalla. */
void GameWorld::setScreenSize(VectorXY screenSize) {
	this->screenSize = screenSize;
}

/* Devuelve el tamanyo del mundo de box2d. */
VectorXY GameWorld::getBox2DWorldSize() {
	return this->box2DSize;
}

void GameWorld::setMainEntity(int index) {
	this->updateMutex.lock();
	this->mainEntity = this->searchEntity(index);
	this->updateMutex.unlock();
}

GameEntity * GameWorld::searchEntity(int index) {
	return this->entityMap[index];
}

/* Agrega un GameEntity. */
void GameWorld::addEntity(GameEntity * entity) {
	this->entityMap[entity->getIndex()] = entity;
}

/* Realiza los updates. */
void GameWorld::update(unsigned int delta) {
	this->updateMutex.lock();
	int currentTime = Global::game->getElapsedTime();

	/*
	 if(updatesList.size() == 0){
	 this->afkTime += delta;

	 if(this->afkTime > 3000){
	 Global::game->showErrorMessage("Problema de conexion", "Se ha interrumpido la conexion con el servidor");
	 Global::game->endGame();
	 }

	 this->updateMutex.unlock();
	 return;
	 }
	 */
	for(auto * u : updateList){
		entityMap[u->index]->addUpdateRequest(u, currentTime);
	}

	updateList.clear();

	this->afkTime = 0;
	for (auto entity : this->entityMap) {
		entity.second->update(delta);
	}


	this->updateMutex.unlock();
}

/* Agrega pedido de request. */
void GameWorld::addUpdateRequest(UpdateRequest * update) {
	this->updateMutex.lock();

	//entityMap[update->index]->addUpdateRequest(update, );
	updateList.push_back(update);
	//;
	this->updateMutex.unlock();
}

/* Devuelve entityList.*/
std::map<int, GameEntity *> GameWorld::getEntityMap() {
	return this->entityMap;
}

void GameWorld::mutexLock(){
	this->updateMutex.lock();
}

void GameWorld::mutexUnlock(){
	this->updateMutex.unlock();
}

/* Inicializa los componentes graficos. */
void GameWorld::generateGraphics() {
	this->updateMutex.lock();
	for (auto entity : this->entityMap) {
		entity.second->setWorld(this);
		entity.second->initialize();
	}
	this->updateMutex.unlock();
}

VectorXY GameWorld::box2DToSDLSize(VectorXY * box2DCoord) {
	int screenW = this->sdlWorldSize.x;
	int screenH = this->sdlWorldSize.y;

	float sdlX = box2DCoord->x / box2DSize.x * screenW;
	float sdlY = box2DCoord->y / box2DSize.y * screenH;
	VectorXY sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

VectorXY GameWorld::getSdlWorldSize() {
	return this->sdlWorldSize;
}

VectorXY GameWorld::box2DToSDL(VectorXY * box2DCoord) {
	int screenW = this->sdlWorldSize.x;
	int screenH = this->sdlWorldSize.y;

	float sdlX = box2DCoord->x / box2DSize.x * screenW;
	float sdlY = screenH - box2DCoord->y / box2DSize.y * screenH;
	VectorXY sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

GameWorld::~GameWorld() {
	for (auto e : entityMap) {
		delete e.second;
	}
}

