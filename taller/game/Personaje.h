#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"
#include "ContactListener.h"

#include <Box2D/Box2D.h>

// Personaje (tanto jugador como NPC).
class Animation;
class Resources;

class Personaje: public CosaConMovimiento {
protected:
	ContactListener *listenerTouchingGround;
public:
	Personaje(b2World * gameWorld);
	virtual ~Personaje();

	void jump();
	void setListenerTouchingGround(ContactListener *aListener);
	bool isOnAir(); //se sobreescribe la de CosaConMovimiento para agregar el listener

	Animation * getAnimation(Resources * resources);
};

#endif /* PERSONAJE_H_ */
