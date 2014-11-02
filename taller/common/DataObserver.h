/*
 * DataObserver.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef DATAOBSERVER_H_
#define DATAOBSERVER_H_

#include "client_handler.h"
#include "CommandCode.h"
#include "Message.h"

class DataObserver {
public:
	virtual char dataArribal(Message * msg, Client_handler * client) = 0;
	virtual void closeConnection(Client_handler * client) = 0;
	virtual void errorConnection(Client_handler * client, int error) = 0;
};

#endif /* DATAOBSERVER_H_ */
