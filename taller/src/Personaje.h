#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"

// Personaje (tanto jugador como NPC).
// Asumo que el punto (0,0) esta en la esquina
// inferior izquierda de la pantalla. X horizontal
// e Y vertical.
class Personaje {
private:
	// Punto (x,y) en donde esta
	VectorXY posicion;

	// Velocidad en ejes x e y
	VectorXY velocidad;

	// True si tiene buff de velocidad.
	bool buffVelocidad;

	// Velocidades (modulo) maximas por defecto.
	// Asumo que la velocidad vertical no se modificaria.
	const float VELOCIDAD_MAXIMA_DEFAULT_X = 10;
	const float VELOCIDAD_MAXIMA_DEFAULT_Y = 10;
	const float VELOCIDAD_MAXIMA_BUFF_X = VELOCIDAD_MAXIMA_DEFAULT_X * 1.5;

	float velocidadMaximaX;
	float velocidadMaximaY;

	// Limita velocidad de coordenada a velocidadMaxima.
	void limitarVelocidad(float *coordenada, float velocidadMaxima);

public:
	// Inicializa personaje quieto en (x,y), (0,0) por defecto.
	Personaje(int x = 0, int y = 0);

	// Acelera la velocidad del personaje en X e Y. Limitado
	// por la velocidad maxima. Devuelve la nueva velocidad.
	VectorXY acelerarPersonaje(float x, float y);

	// Devuelve la posicion actual.
	VectorXY verPosicionActual();

	// Mueve la posicion del personaje dependiendo de su velocidad.
	void moverPersonaje();

	// Devuelve la posicion a la que se movera el personaje.
	VectorXY siguientePosicion();

	// Frena al personaje en X y/o Y
	void frenarPersonaje(bool frenarEnX, bool frenarEnY);

	// Devuelve true si tiene buff de velocidad.
	bool tieneBuffVelocidad();

	// Le otorga el buff de velocidad.
	void darBuffVelocidad();

	// Le quita el buff de velocidad.
	void quitarBuffVelocidad();
};

#endif /* PERSONAJE_H_ */
