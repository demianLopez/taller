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

void ServerData::dataArribal(char * data, int length, Client_handler * client){
	std::cout<<"Re: "<<length<<" bytes - "<<data<<std::endl;
}

void ServerData::errorConnection(Client_handler * client, int error){

}

ServerData::~ServerData() {
	// TODO Auto-generated destructor stub
}

