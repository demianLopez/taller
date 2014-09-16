#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"

#include "Box2D/Box2D.h"

// Personaje (tanto jugador como NPC).
class Animation;
class Resources;

class Personaje: public CosaConMovimiento {
public:
	Personaje(b2World * gameWorld);
	virtual ~Personaje();

	void jump();
};

#endif /* PERSONAJE_H_ */
