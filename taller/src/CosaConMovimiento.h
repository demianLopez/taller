#ifndef COSACONMOVIMIENTO_H_
#define COSACONMOVIMIENTO_H_

#include "VectorXY.h"

class CosaConMovimiento {	// No puedo pensar un nombre mejor.
private:
	bool mirandoParaLaDerecha;

protected:
	// Punto (x,y) en donde esta
	VectorXY posicion;

	// Velocidad en ejes x e y
	VectorXY velocidad;

public:
	// Inicializa cosa quieta en (x,y), (0,0) por defecto.
	CosaConMovimiento(float x = 0, float y = 0);

	// Mueve la posicion de la cosa dependiendo de su velocidad.
	void mover();

	// Devuelve la posicion actual.
	VectorXY verPosicionActual();

	// Devuelve la posicion a la que se movera la cosa.
	VectorXY siguientePosicion();

	// Frena la cosa en X y/o Y
	void frenar(bool frenarEnX, bool frenarEnY);

	// Devuelve true si esta mirando para la derecha.
	bool estaMirandoParaLaDerecha();
};

#endif /* COSACONMOVIMIENTO_H_ */
