/*
 * ClientData.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include <ClientData.h>
#include <iostream>
#include "Global.h"
#include "entity/PolygonEntity.h"
#include <UpdateRequest.h>

ClientData::ClientData() {
	// TODO Auto-generated constructor stub
}

void ClientData::closeConnection(Client_handler * client){
	this->backMainMenu();
}

void ClientData::dataArribal(Message * m, Client_handler * client){
	char cCode = m->getCommandCode();

	if(cCode == UPDATE_ENTITY){
		UpdateRequest * uR = new UpdateRequest();
		uR->index = m->getChar();
		uR->posX = m->getFloat();
		uR->posY = m->getFloat();
		uR->rotation = m->getFloat();
		Global::gameWorld->addUpdateRequest(uR);
	}

	if(cCode == SERVER_DATA){
		char * serverName;
		char l = m->getCharArray(&serverName);
		Global::mainMenu->setServerInfo(serverName, m->getChar(), m->getChar());
		return;
	}

	if(cCode == ERROR_MESSAGE){
		char * msg;
		char * title;

		m->getCharArray(&title);
		m->getCharArray(&msg);

		Global::game->showErrorMessage(title, msg);

		delete[] msg;
		delete[] title;
		return;
	}

	if(cCode == INITIALIZE_MAP){
		float tX = m->getFloat();
		float tY = m->getFloat();
		Global::gameWorld = new GameWorld(tX, tY);
		return;
	}

	if(cCode == ADD_MAP_DATA){
		int index = m->getChar();
		int t = m->getChar();
		float pX = m->getFloat();
		float pY = m->getFloat();

		float rotation = m->getFloat();

		PolygonEntity * pEnt = new PolygonEntity(index);
		pEnt->setPosition(pX, pY);
		pEnt->setRotation(rotation);

		for(int i = 0; i< t; i++){
			float tX = m->getFloat();
			float tY = m->getFloat();

			pEnt->addVertex(tX, tY);
		}

		Global::gameWorld->addEntity(pEnt);
		return;
	}

	if(cCode == INITIALIZE_GRAPHICS){
		Global::levelState->setWorld(Global::gameWorld);
		Global::game->enterState(1);
		return;
	}

}

void ClientData::errorConnection(Client_handler * client, int error){
	this->backMainMenu();
}

void ClientData::backMainMenu(){
	Global::game->enterState(0);
	Global::game->showErrorMessage("Error de conexion",
			"Se perdio la conexion con el servidor.");
}

ClientData::~ClientData() {
	// TODO Auto-generated destructor stub
}

