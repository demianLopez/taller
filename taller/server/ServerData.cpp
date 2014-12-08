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
					if(Data::world->isOnLoop() || Data::world->changin){
						envio.addCommandCode(ERROR_MESSAGE);
						envio.addCharArray("Jugador desconectado\0", 22);
						envio.addCharArray(
								"Ha abandonado una partida en curso, debera esperar a que termine para unirse nuevamente\0",
								89);
						envio.addEndChar();
						client->send_message(&envio);
						return cCode;
					} else {
						reconecting = true;
						reconectedPlayer = p;
					}
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

		Data::world->sendWorldInfo(client);

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

		Data::world->checkPlayerCount();

		return cCode;
	}

	if (cCode == PLAYER_READY) {
		Jugador * p = Data::world->getPlayer(client->userIndex);
		p->playerBusy.lock();
		p->isReady = true;
		p->playerBusy.unlock();
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

