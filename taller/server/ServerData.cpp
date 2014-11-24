/*
 * ServerData.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include "ServerData.h"
#include "Jugador.h"
#include "Data.h"
#include <string>

using std::string;

ServerData::ServerData(Server * sv) {
	this->sv = sv;
}

void ServerData::closeConnection(Client_handler * client) {
	this->disconnectPlayer(Data::world->getPlayer(client->userIndex));
}

void ServerData::disconnectPlayer(Jugador * j) {
	if (j != NULL) {
		j->setOffline(true);

		Message m;
		m.addCommandCode(SHOW_MESSAGE);
		string pM("");
		pM.append(j->getName());
		pM.append(" se ha desconectado");
		m.addCharArray(pM.c_str(), pM.size());
		m.addEndChar();

		Data::world->sendToWorldPlayers(&m);
	}
}

char ServerData::dataArribal(Message * m, Client_handler * client) {
	Message envio = Message();
	//std::cout<<"Re: "<<m->getMessageLength()<<" bytes - "<<m->getMessageData()<<std::endl;
	char cCode = m->getCommandCode();
	if (cCode == IM_LOGGED) {
		envio.addCommandCode(SERVER_DATA);
		envio.addCharArray(Data::world->getWorldName()->c_str(),
				Data::world->getWorldName()->size());
		envio.addChar(Data::world->getMaxPlayers()); //Maxima cantidad de jugadores permitida
		char cantidadJugando = Data::world->getPlayerList().size();
		envio.addChar(cantidadJugando);
		envio.addEndChar();
		client->send_message(&envio);
		return cCode;
	}

	if (cCode == KEY_EVENT) {
		Jugador * j = Data::world->getPlayer(client->userIndex);

		int keyData = m->getChar();

		for (int i = 0; i < keyData; i++) {
			j->addKeyCode(m->getKeyCode());
		}

		return cCode;
	}

	if (cCode == IM_ALIVE) {
		Jugador * j = Data::world->getPlayer(client->userIndex);
		j->keyRequestSend = 0;
		return cCode;
	}

	if (cCode == LOGGIN_GAME) {
		vector<Jugador *> lPlayer = Data::world->getPlayerList();
		char * playerName;
		m->getCharArray(&playerName);
		string nm(playerName);

		// Comparacion para ver si ya existe el nombre en uso.
		bool reconecting = false;
		Jugador * reconectedPlayer = NULL;
		for (auto * p : lPlayer) {
			string oPlayer(p->getName());
			if (oPlayer.compare(nm) == 0) {
				if (p->isOffline()) {
					reconecting = true;
					reconectedPlayer = p;
					break;
				} else {
					envio.addCommandCode(ERROR_MESSAGE);
					envio.addCharArray("Jugador Online\0", 15);
					envio.addCharArray(
							"El nombre que intenta utilizar se encuentra en uso\0",
							51);
					envio.addEndChar();
					client->send_message(&envio);
					return cCode;
				}
			}
		}
		// Ver si ya esta lleno.
		if (!reconecting) {
			if (Data::world->getPlayerList().size()
					>= Data::world->getMaxPlayers()) {
				envio.addCommandCode(ERROR_MESSAGE);
				envio.addCharArray("Lugares\0", 8);
				envio.addCharArray("No hay mas lugar\0", 17);
				envio.addEndChar();
				client->send_message(&envio);
				return cCode;
			}
		}
		//Mandamos un mensaje por poligono!
		envio.addCommandCode(INITIALIZE_MAP);
		envio.addFloat(&Data::world->getBox2DWorldSize()->x);
		envio.addFloat(&Data::world->getBox2DWorldSize()->y);
		envio.addChar(Data::world->isWaitingForPlayers());
		envio.addEndChar();
		client->send_message(&envio);
		vector<Polygon*> polList = Data::world->getPolygonList();
		for (auto * p : polList) {
			Message * mapData = new Message();
			mapData->addCommandCode(ADD_MAP_DATA);
			char vNum = p->getPointList().size();
			mapData->addChar(p->getEntityIndex());
			mapData->addChar(p->isStatic());
			mapData->addChar(p->getType());
			mapData->addChar(vNum);
			mapData->addFloat(&p->getPosition()->x);
			mapData->addFloat(&p->getPosition()->y);
			float rotation = p->getRotation();
			mapData->addFloat(&rotation);
			for (auto * ver : p->getPointList()) {
				mapData->addFloat(&ver->x);
				mapData->addFloat(&ver->y);
			}
			mapData->addEndChar();
			client->send_message(mapData);
			delete mapData;
		}
		Jugador * j;
		if (!reconecting) {
			Message m;
			m.addCommandCode(SHOW_MESSAGE);
			string pM("");
			pM.append(playerName);
			pM.append(" se ha conectado");
			m.addCharArray(pM.c_str(), pM.size());
			m.addEndChar();
			Data::world->sendToWorldPlayers(&m);
			j = new Jugador(client, playerName);
			j->setOffline(false); //FIXME: agregue esto porque sino queda sin inicializar. No se si va en false..
		} else {
			Message m;
			m.addCommandCode(SHOW_MESSAGE);
			string pM("");
			pM.append(reconectedPlayer->getName());
			pM.append(" se ha reconectado");
			m.addCharArray(pM.c_str(), pM.size());
			m.addEndChar();
			Data::world->sendToWorldPlayers(&m);
			client->userIndex = reconectedPlayer->getIndex();
			reconectedPlayer->setClient(client);
			j = reconectedPlayer;
			j->setOffline(false);
		}
		Data::world->addPlayer(j, reconecting);
		Message * mainEntity = new Message();
		mainEntity->addCommandCode(LOCK_CAMERA_ENTITY);
		char mEntity = j->getIndex();
		mainEntity->addChar(mEntity);
		mainEntity->addEndChar();
		client->send_message(mainEntity);
		delete mainEntity;
		Message * finalData = new Message();
		finalData->addCommandCode(INITIALIZE_GRAPHICS);
		finalData->addChar(j->getPlayerLives());
		finalData->addChar(j->getPlayerScore());
		finalData->addEndChar();
		client->send_message(finalData);
		delete finalData;
		return cCode;
	}

	std::cout << "WARNING: LOOSING cCode: " << (int) cCode << endl;
	return cCode;
}

void ServerData::errorConnection(Client_handler * client, int error) {
	this->disconnectPlayer(Data::world->getPlayer(client->userIndex));
}

ServerData::~ServerData() {
}

