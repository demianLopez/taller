#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Personaje.h"
#include "BolaDeNieve.h"

class Jugador: public Personaje {
private:
	// True si tiene buff de velocidad.
	bool buffVelocidad;

	// Velocidades (modulo) maximas por defecto.
	// Asumo que la velocidad vertical no se modificaria.
	const float VELOCIDAD_MAXIMA_DEFAULT_X = 50;
	const float VELOCIDAD_MAXIMA_DEFAULT_Y = 50;
	const float VELOCIDAD_MAXIMA_BUFF_X = VELOCIDAD_MAXIMA_DEFAULT_X * 1.5;

public:
	// Inicializa Jugador quieto en (x,y), (0,0) por defecto.
	Jugador(float x = 0, float y = 0);

	// Devuelve true si tiene buff de velocidad.
	bool tieneBuffVelocidad();

	// Le otorga el buff de velocidad.
	void darBuffVelocidad();

	// Le quita el buff de velocidad.
	void quitarBuffVelocidad();

	// Dispara una bola de nieve. Devuelve la BolaDeNieve arrojada.
	BolaDeNieve disparar();
};

#endif /* JUGADOR_H_ */
