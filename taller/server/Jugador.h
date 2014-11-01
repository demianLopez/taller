#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Personaje.h"
#include "BolaDeNieve.h"

// Jugador principal
class Jugador {
private:


	char * name;
	int userIndex;


	/*
	 const float VELOCIDAD_MAXIMA_BUFF_X = VELOCIDAD_MAXIMA_DEFAULT_X * 1.5;
	 */

public:

	Jugador(int userIndex, char * name);
	char * getName();

};

#endif /* JUGADOR_H_ */
