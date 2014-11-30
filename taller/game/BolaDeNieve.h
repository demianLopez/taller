#ifndef BOLADENIEVE_H_
#define BOLADENIEVE_H_

#include "../server/CosaConMovimiento.h"
#include "VectorXY.h"

class BolaDeNieve: public CosaConMovimiento {
private:
	const float VELOCIDAD_EN_X = 100;
	const float VELOCIDAD_EN_Y = -10;

	VectorXY posicionOriginal;
	// Despues de una distancia, desaparece.
	bool viva; //TODO: implementar esto.
public:
	// Crea una BolaDeNieve con la direccion indicada.
	BolaDeNieve(bool haciaLaDerecha, float x = 0, float y = 0);
	BolaDeNieve(bool haciaLaDerecha, VectorXY posicion);
};

#endif /* BOLADENIEVE_H_ */
