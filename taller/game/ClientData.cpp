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
		if(Global::game->isOnState(1)){
			Global::gameWorld->addUpdateRequest(uR);
		}
		return cCode;

	}

	if (cCode == REQUEST_KEY_DATA) {
		Global::levelState->sendKeyData();
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

		char * pName = new char[50]; //Lo Libera PlayerEntity
		m->getCharArray(&pName);

		PlayerEntity * pEntity = new PlayerEntity(index);
		pEntity->setPosition(pX, pY);
		pEntity->setAnimation(anim);
		pEntity->setPlayerName(pName);

		pEntity->setWorld(Global::gameWorld);
		Global::gameWorld->addEntity(pEntity);

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
		pEnt->setStatic(isStatic);
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
		Global::game->enterState(1);
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

		for(int i = 0; i < playerCount; i++){
			char * name;
			m->getCharArray(&name);
			playerNames[i] = string(name);
			playerScores[i] = m->getChar();
			playerConected[i] = m->getChar();
			delete[] name;
		}

		bool winGame  = m->getChar();
		Global::changeState->setLevelData(playerNames, playerScores, winGame, playerCount, playerConected);
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

