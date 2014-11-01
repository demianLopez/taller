/*
 * ClientData.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include <ClientData.h>
#include <iostream>
#include "Global.h"

ClientData::ClientData() {
	// TODO Auto-generated constructor stub
}

void ClientData::closeConnection(Client_handler * client){

}

void ClientData::dataArribal(Message * m, Client_handler * client){
	char cCode = m->getCommandCode();

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
}

void ClientData::errorConnection(Client_handler * client, int error){

}

ClientData::~ClientData() {
	// TODO Auto-generated destructor stub
}

