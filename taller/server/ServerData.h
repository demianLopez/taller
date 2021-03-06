/*
 * ServerData.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef SERVERDATA_H_
#define SERVERDATA_H_

#include "../common/DataObserver.h"
#include "Server.h"
#include "Jugador.h"

class ServerData: public DataObserver {
public:
	ServerData(Server * sv);
	char dataArribal(Message * m, Client_handler * client);
	void closeConnection(Client_handler * client);
	void errorConnection(Client_handler * client, int error);
	virtual ~ServerData();

	void disconnectPlayer(Jugador * j);
private:
	Server * sv;
};

#endif /* SERVERDATA_H_ */
