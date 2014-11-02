#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Personaje.h"
#include "BolaDeNieve.h"
#include <client_handler.h>

// Jugador principal
class Jugador : public Personaje {
private:


	char * name;

	Client_handler * client;

	/*
	 const float VELOCIDAD_MAXIMA_BUFF_X = VELOCIDAD_MAXIMA_DEFAULT_X * 1.5;
	 */

public:

	Jugador(Client_handler * client, char * name);
	char * getName();


	Client_handler * getClient();
};

#endif /* JUGADOR_H_ */
