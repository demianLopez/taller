/*
 * ClientData.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include "ClientData.h"
#include <iostream>
#include "Global.h"
#include "entity/PolygonEntity.h"
#include "entity/PlayerEntity.h"
#include "entity/EnemyEntity.h"
#include "entity/ProjectileEntity.h"
#include "entity/BonusEntity.h"
#include "entity/WaterEntity.h"
#include "../common/UpdateRequest.h"

ClientData::ClientData() {
}

/* Cierra la conexion cuando se pierde la conexion con el server.
 * Vuelve al menu principal. */
void ClientData::closeConnection(Client_handler * client) {
	this->backMainMenu();
}

/* Procesa la informacion proveniente del server.
 * Realiza distintas acciones dependiendo del codigo que traiga
 * el mensaje. */
char ClientData::dataArribal(Message * m, Client_handler * client) {
	char cCode = m->getCommandCode();

	if (Global::game->isClosing()) {
		return CLOSING_GAME;
	}

	if (cCode == UPDATE_ENTITY) {

		UpdateRequest * uR = new UpdateRequest();
		uR->index = m->getChar();
		uR->posX = m->getFloat();
		uR->posY = m->getFloat();
		uR->rotation = m->getFloat();
		if(Global::game->isOnState(1)){
			Global::gameWorld->addUpdateRequest(uR);
		}
		return cCode;
	}

	if (cCode == UPDATE_PLAYER_ENTITY) {

		UpdateRequest * uR = new UpdateRequest();
		uR->index = m->getChar();
		uR->posX = m->getFloat();
		uR->posY = m->getFloat();
		uR->animation = m->getAnimationCode();
		uR->offline = m->getChar();
		uR->invulnerable = m->getChar();
		if(Global::game->isOnState(1)){
			Global::gameWorld->addUpdateRequest(uR);
		}
		return cCode;

	}

	if (cCode == UPDATE_ENEMY_ENTITY) {
		UpdateRequest * uR = new UpdateRequest();
		uR->index = m->getChar();
		uR->posX = m->getFloat();
		uR->posY = m->getFloat();
		uR->rotation = m->getFloat();
		uR->animation = m->getAnimationCode();
		if(Global::game->isOnState(1)){
			Global::gameWorld->addUpdateRequest(uR);
		}
		return cCode;
	}

	if (cCode == REQUEST_KEY_DATA) {
		Global::levelState->sendKeyData();
		return cCode;
	}

	if(cCode == ACTIVE_ENTITY){
		int entityNumber = m->getChar();
		bool active = m->getChar();
		Global::gameWorld->searchEntity(entityNumber)->setActive(active);
		return cCode;
	}

	if (cCode == UPDATE_TIMING) {
		char timing = m->getChar();
		Global::serverUpdateTiming = timing;
		return cCode;
	}

	if (cCode == SERVER_DATA) {
		char * serverName;
		char l = m->getCharArray(&serverName);
		Global::mainMenu->setServerInfo(serverName, m->getChar(), m->getChar());
		return cCode;
	}

	if(cCode == SHOOT_PROJECTILE){
		int indx = m->getChar();
		float posX = m->getFloat();
		float posY = m->getFloat();

		GameEntity * gE = Global::gameWorld->searchEntity(indx);
		gE->setPosition(posX, posY);
		gE->setActive(true);

		return cCode;
	}

	if(cCode == FORCE_POSITION){
		int index = m->getChar();
		float posX = m->getFloat();
		float posY = m->getFloat();

		bool forceCamara = m->getChar();

		Global::gameWorld->searchEntity(index)->forcePosition(posX, posY);
		if(forceCamara){
			Global::gameWorld->setMainEntity(index);
			Global::levelState->restartCameraPosition();
		}
		return cCode;
	}

	if (cCode == ERROR_MESSAGE) {
		char * msg;
		char * title;

		m->getCharArray(&title);
		m->getCharArray(&msg);

		Global::game->showErrorMessage(title, msg);

		delete[] msg;
		delete[] title;
		return cCode;
	}

	if(cCode == PUT_BONUS){
		int index = m->getChar();
		float xPos = m->getFloat();
		float yPos = m->getFloat();
		int type = m->getChar();

		BonusEntity * bE = (BonusEntity*) Global::gameWorld->searchEntity(index);
		bE->putAt(xPos, yPos, type);

		return cCode;
	}

	if (cCode == INITIALIZE_MAP) {
		float tX = m->getFloat();
		float tY = m->getFloat();
		Global::gameWorld = new GameWorld(tX, tY);
		Global::gameWorld->setWaitingForPlayers(m->getChar());
		return cCode;
	}

	if (cCode == ADD_PLAYER_DATA) {
		char index = m->getChar();
		float pX = m->getFloat();
		float pY = m->getFloat();
		AnimationCode anim = m->getAnimationCode();

		//char * pName = new char[50]; //Lo Libera PlayerEntity
		char *pName; //Lo libera player entity (en la siguiente linea se le asigna memoria).
		m->getCharArray(&pName);

		PlayerEntity * pEntity = new PlayerEntity(index);
		pEntity->setPosition(pX, pY);
		pEntity->setAnimation(anim);
		pEntity->setPlayerName(pName);

		pEntity->setWorld(Global::gameWorld);
		Global::gameWorld->addEntity(pEntity);

		return cCode;
	}

	if(cCode == ADD_ENEMY_DATA){
		char index = m->getChar();
		int type = m->getChar();
		float pX = m->getFloat();
		float pY = m->getFloat();
		AnimationCode anim = m->getAnimationCode();

		EnemyEntity * enemyEntity = new EnemyEntity(index, type);
		enemyEntity->setPosition(pX, pY);
		enemyEntity->setAnimation(anim);

		Global::gameWorld->addEntity(enemyEntity);
		return cCode;
	}

	if (cCode == ADD_MAP_DATA) {
		int index = m->getChar();
		char isStatic = m->getChar();
		char type = m->getChar();
		int t = m->getChar();
		float pX = m->getFloat();
		float pY = m->getFloat();

		float rotation = m->getFloat();

		PolygonEntity * pEnt = new PolygonEntity(index);
		pEnt->setUpdateable(!isStatic);
		pEnt->setPosition(pX, pY);
		pEnt->setRotation(rotation);
		pEnt->setType(type);

		for (int i = 0; i < t; i++) {
			float tX = m->getFloat();
			float tY = m->getFloat();

			pEnt->addVertex(tX, tY);
		}

		pEnt->setWorld(Global::gameWorld);
		Global::gameWorld->addEntity(pEnt);
		return cCode;
	}

	if (cCode == ADD_WATER) {
		int index = m->getChar();
		float pX = m->getFloat();
		float pY = m->getFloat();
		float w = m->getFloat();
		float h = m->getFloat();

		WaterEntity * waterEntity = new WaterEntity(index);
		waterEntity->setPosition(pX, pY);
		waterEntity->size = VectorXY(w, h);
		waterEntity->setWorld(Global::gameWorld);
		Global::gameWorld->addEntity(waterEntity);

		return cCode;
	}

	if(cCode == INSTANTIATE_BONUS){
		char min = m->getChar();
		char max = m->getChar();

		for(int i = min; i <= max; i++){
			BonusEntity * bE = new BonusEntity(i);
			bE->setActive(false);
			Global::gameWorld->addEntity(bE);
		}
		return cCode;
	}

	if(cCode == INSTANTIATE_PROJECTILES){
		int nMin = m->getChar();
		int nMax = m->getChar();
		int type = m->getChar();

		for(int i = nMin; i <= nMax; i++){
			ProjectileEntity * p = new ProjectileEntity(i, type);
			p->setActive(false);
			Global::gameWorld->addEntity(p);
		}
		return cCode;
	}

	if (cCode == INITIALIZE_GRAPHICS) {
		Global::levelState->setWorld(Global::gameWorld);
		Global::playerLife = m->getChar();
		Global::playerScore = m->getChar();
		Global::game->enterState(1);
		return cCode;
	}

	if (cCode == UPDATE_PLAYER_STAT) {
		Global::levelState->setWorld(Global::gameWorld);
		Global::playerLife = m->getChar();
		Global::playerScore = m->getChar();
		return cCode;
	}

	if(cCode == START_GAME){
		Global::gameWorld->setWaitingForPlayers(false);
		return cCode;
	}

	if (cCode == LOCK_CAMERA_ENTITY) {
		char entityIndex = m->getChar();
		Global::gameWorld->setMainEntity(entityIndex);
		Global::levelState->restartCameraPosition();
		return cCode;
	}

	if(cCode == END_LEVEL){
		char playerCount = m->getChar();

		string * playerNames = new string[playerCount];
		int * playerScores = new int[playerCount];
		bool * playerConected = new bool[playerCount];
		bool * muertes = new bool[playerCount];

		for(int i = 0; i < playerCount; i++){
			char * name;
			m->getCharArray(&name);
			playerNames[i] = string(name);
			playerScores[i] = m->getChar();
			playerConected[i] = m->getChar();
			muertes[i] = m->getChar();
			delete[] name;
		}

		bool winGame  = m->getChar();
		bool muerto = m->getChar();
		Global::changeState->setLevelData(playerNames, playerScores, winGame, playerCount, playerConected, muertes, muerto);
		Global::game->enterState(2);
		return cCode;
	}

	if (cCode == SHOW_MESSAGE) {
		char * message;
		m->getCharArray(&message);
		Global::levelState->setMessage(message);
		return cCode;
	}

	std::cout << "WARNING: LOOSING cCode: " << (int) cCode << endl;
	return cCode;
}

/* Cierra la conexion cuando se pierde la conexion con el server.
 * Vuelve al menu principal.
 * FIXME: Hace exactamente lo mismo que closeConnection, solo
 * que ademas recibe error. */
void ClientData::errorConnection(Client_handler * client, int error) {
	this->backMainMenu();
}

/* Cambia el estado del juego y muestra un mensaje de error
 * de conexion. */
void ClientData::backMainMenu() {
	Global::game->enterState(0);
	if (!Global::game->isClosing()) {
		Global::game->showErrorMessage("Error de conexion",
				"Se perdio la conexion con el servidor.");
	}
}

ClientData::~ClientData() {
}

