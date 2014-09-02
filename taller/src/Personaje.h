#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"

// Personaje (tanto jugador como NPC).
// Asumo que el punto (0,0) esta en la esquina
// inferior izquierda de la pantalla. X horizontal
// e Y vertical.
class Personaje: public CosaConMovimiento {
private:
	// Limita velocidad de coordenada a velocidadMaxima.
	void limitarVelocidad(float *coordenada, float velocidadMaxima);

protected:
	// Velocidad maxima a la que se puede acelerar.
	float velocidadMaximaX;
	float velocidadMaximaY;

public:
	// Acelera la velocidad del personaje en X e Y. Limitado
	// por la velocidad maxima.
	void acelerarPersonaje(float x, float y);

};

#endif /* PERSONAJE_H_ */
