#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Personaje.h"
#include "BolaDeNieve.h"

// Jugador principal
class Jugador: public Personaje {
private:
	// True si tiene buff de velocidad.
	//bool buffVelocidad;

	// Velocidades (modulo) maximas por defecto.
	const float MOVEMENT_SPEED_X = 4;
	const float MOVEMENT_SPEED_Y = 13;


	b2Vec2 size;
	/*
	const float VELOCIDAD_MAXIMA_BUFF_X = VELOCIDAD_MAXIMA_DEFAULT_X * 1.5;
	*/

public:
	// Inicializa Jugador.
	b2Vec2 getSize();
	Jugador(b2World * gameWorld);
	//virtual ~Jugador();

	// Devuelve true si tiene buff de velocidad.
	//bool tieneBuffVelocidad();

	// Le otorga el buff de velocidad.
	//void darBuffVelocidad();

	// Le quita el buff de velocidad.
	//void quitarBuffVelocidad();

	// Dispara una bola de nieve. Devuelve la BolaDeNieve arrojada.
	//BolaDeNieve disparar();
};

#endif /* JUGADOR_H_ */
