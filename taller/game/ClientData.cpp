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

ClientData::ClientData() {
	// TODO Auto-generated constructor stub
}

void ClientData::closeConnection(Client_handler * client) {

}

void ClientData::dataArribal(Message * m, Client_handler * client) {
	char cCode = m->getCommandCode();

	if (cCode == SERVER_DATA) {
		char * serverName;
		char l = m->getCharArray(&serverName);
		Global::mainMenu->setServerInfo(serverName, m->getChar(), m->getChar());
		return;
	}

	if (cCode == ERROR_MESSAGE) {
		char * msg;
		char * title;

		m->getCharArray(&title);
		m->getCharArray(&msg);

		Global::game->showErrorMessage(title, msg);

		delete[] msg;
		delete[] title;
		return;
	}

	if (cCode == INITIALIZE_MAP) {
		float tX = m->getFloat();
		float tY = m->getFloat();
		Global::gameWorld = new GameWorld(tX, tY);
		return;
	}

	if (cCode == ADD_MAP_DATA) {
		int t = m->getChar();
		PolygonEntity * pEnt = new PolygonEntity(0);
		for (int i = 0; i < t; i++) {
			float tX = m->getFloat();
			float tY = m->getFloat();

			pEnt->addVertex(tX, tY);
		}

		Global::gameWorld->addEntity(pEnt);
		return;
	}

	if (cCode == INITIALIZE_GRAPHICS) {
		Global::levelState->setWorld(Global::gameWorld);
		Global::game->enterState(1);
		return;
	}

}

void ClientData::errorConnection(Client_handler * client, int error) {

}

ClientData::~ClientData() {
	// TODO Auto-generated destructor stub
}

