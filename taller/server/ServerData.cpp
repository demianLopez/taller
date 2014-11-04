/*
 * ServerData.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include <ServerData.h>
#include "Jugador.h"
#include "Data.h"
#include <string>

ServerData::ServerData(Server * sv) {
	this->sv = sv;
}

void ServerData::closeConnection(Client_handler * client){

}

char ServerData::dataArribal(Message * m, Client_handler * client){
	Message envio = Message();
	//std::cout<<"Re: "<<m->getMessageLength()<<" bytes - "<<m->getMessageData()<<std::endl;
	char cCode = m->getCommandCode();
	if(cCode == IM_LOGGED){
		std::cout<<"loged"<<endl;
		envio.addCommandCode(SERVER_DATA);
		envio.addCharArray(Data::world->getWorldName()->c_str(), Data::world->getWorldName()->size());
		envio.addChar(Data::world->getMaxPlayers()); //Maxima cantidad de jugadores permitida
		char cantidadJugando = Data::world->getPlayerList().size();
		envio.addChar(cantidadJugando);
		envio.addEndChar();
		client->send_message(&envio);
		return cCode;
	}

	if(cCode == KEY_EVENT){
		Jugador * j = Data::world->getPlayer(client->userIndex);

		int keyData = m->getChar();

		for(int i = 0; i < keyData; i++){
			j->addKeyCode(m->getKeyCode());
		}

		return cCode;
	}

	if(cCode == LOGGIN_GAME){

		vector<Jugador *> lPlayer = Data::world->getPlayerList();
		char * playerName;
		m->getCharArray(&playerName);

		string nm(playerName);

		// Ver si ya esta lleno.
		if (Data::world->getPlayerList().size() >= Data::world->getMaxPlayers()){
			envio.addCommandCode(ERROR_MESSAGE);
			envio.addCharArray("Lugares\0", 8);
			envio.addCharArray("No hay mas lugar\0", 17);
			envio.addEndChar();
			client->send_message(&envio);
			return cCode;
		}

		// Comparacion para ver si ya existe el nombre en uso.
		for(auto * p : lPlayer){
			string oPlayer(p->getName());

			if(oPlayer.compare(nm) == 0){
				envio.addCommandCode(ERROR_MESSAGE);
				envio.addCharArray("Jugador Online\0", 15);
				envio.addCharArray("El nombre que intenta utilizar se encuentra en uso\0", 51);
				envio.addEndChar();
				client->send_message(&envio);
				return cCode;
			}
		}

		//Mandamos un mensaje por poligono!
		envio.addCommandCode(INITIALIZE_MAP);
		envio.addFloat(&Data::world->getBox2DWorldSize()->x);
		envio.addFloat(&Data::world->getBox2DWorldSize()->y);
		envio.addEndChar();
		client->send_message(&envio);

		vector<Polygon*> polList = Data::world->getPolygonList();

		for(auto * p : polList){
			Message * mapData = new Message();
			mapData->addCommandCode(ADD_MAP_DATA);

			char vNum = p->getPointList().size();
			mapData->addChar(p->getEntityIndex());
			mapData->addChar(p->isStatic());
			mapData->addChar(vNum);
			mapData->addFloat(&p->getPosition()->x);
			mapData->addFloat(&p->getPosition()->y);
			float rotation = p->getRotation();
			mapData->addFloat(&rotation);

			for(auto * ver : p->getPointList()){
				mapData->addFloat(&ver->x);
				mapData->addFloat(&ver->y);
			}

			mapData->addEndChar();
			client->send_message(mapData);


			delete mapData;
		}

		Jugador * j = new Jugador(client, playerName);
		Data::world->addPlayer(j);

		Message * mainEntity = new Message();
		mainEntity->addCommandCode(LOCK_CAMERA_ENTITY);
		char mEntity = j->getIndex();
		mainEntity->addChar(mEntity);
		mainEntity->addEndChar();
		client->send_message(mainEntity);
		delete mainEntity;

		Message * finalData = new Message();
		finalData->addCommandCode(INITIALIZE_GRAPHICS);
		finalData->addEndChar();
		client->send_message(finalData);
		delete finalData;

		return cCode;
	}

	std::cout<<"WARNING: LOOSING cCode: "<<(int)cCode<<endl;
	return cCode;
}

void ServerData::errorConnection(Client_handler * client, int error){

}



ServerData::~ServerData() {
	// TODO Auto-generated destructor stub
}

