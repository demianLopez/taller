/*
 * ClientData.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef CLIENTDATA_H_
#define CLIENTDATA_H_

#include "../common/DataObserver.h"

class ClientData: public DataObserver {
public:
	ClientData();
	/* Procesa la informacion proveniente del server.
	 * Realiza distintas acciones dependiendo del codigo que traiga
	 * el mensaje. */
	char dataArribal(Message * m, Client_handler * client);
	/* Cierra la conexion cuando se pierde la conexion con el server.
	 * Vuelve al menu principal. */
	void closeConnection(Client_handler * client);
	/* Cierra la conexion cuando se pierde la conexion con el server.
	 * Vuelve al menu principal.
	 * FIXME: Hace exactamente lo mismo que closeConnection, solo
	 * que ademas recibe error. */
	void errorConnection(Client_handler * client, int error);
	virtual ~ClientData();
private:
	/* Cambia el estado del juego y muestra un mensaje de error
	 * de conexion. */
	void backMainMenu();
};

#endif /* CLIENTDATA_H_ */
