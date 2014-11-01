/*
 * ClientData.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef CLIENTDATA_H_
#define CLIENTDATA_H_

#include <DataObserver.h>

class ClientData: public DataObserver {
public:
	ClientData();
	void dataArribal(Message * m, Client_handler * client);
	void closeConnection(Client_handler * client);
	void errorConnection(Client_handler * client, int error);
	virtual ~ClientData();
};

#endif /* CLIENTDATA_H_ */
