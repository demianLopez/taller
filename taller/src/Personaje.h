#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"

#include "Box2D/Box2D.h"

// Personaje (tanto jugador como NPC).
// Asumo que el punto (0,0) esta en la esquina
// inferior izquierda de la pantalla. X horizontal
// e Y vertical.

class Animation;
class Resources;

class Personaje: public CosaConMovimiento {
private:
	// Limita velocidad de coordenada a velocidadMaxima.
	void limitarVelocidad(float *coordenada, float velocidadMaxima);
	// Personaje en box2d
	b2Body * mainCharacterBody;

protected:
	// Velocidad maxima a la que se puede acelerar.
	float velocidadMaximaX;
	float velocidadMaximaY;

public:
	Personaje(b2World * gameWorld);
	virtual ~Personaje();

	void update();

	Animation * getAnimation(Resources * resources);
	void moveLeft();
	void moveRight();
	void jump();
	void stop(bool stopX = true, bool stopY = true);

	b2Body * getBody();
	// Acelera la velocidad del personaje en X e Y. Limitado
	// por la velocidad maxima.
	void acelerarPersonaje(float x, float y);
	bool stopAtHit;

	bool goingUp;
	bool goingDown;
	bool onTopJump;

	bool isOnAir();

};

#endif /* PERSONAJE_H_ */
