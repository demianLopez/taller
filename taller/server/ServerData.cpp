/*
 * ServerData.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include <ServerData.h>

ServerData::ServerData(Server * sv) {
	this->sv = sv;
}

void ServerData::closeConnection(Client_handler * client){

}

void ServerData::dataArribal(Message * m, Client_handler * client){
	Message envio = Message();
	//std::cout<<"Re: "<<m->getMessageLength()<<" bytes - "<<m->getMessageData()<<std::endl;
	if(m->getCommandCode() == IM_LOGGED){

		envio.addCommandCode(SERVER_DATA);
		envio.addCharArray("Un mapa de snowBross\0", 21);
		envio.addChar(0);
		envio.addChar(4);
		client->send_message(&envio);
		return;
	}
}

void ServerData::errorConnection(Client_handler * client, int error){

}

ServerData::~ServerData() {
	// TODO Auto-generated destructor stub
}

