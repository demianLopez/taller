#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"
#include "ContactListener.h"

#include <Box2D/Box2D.h>

// Personaje (tanto jugador como NPC).
class Animation;
class Resources;

class Personaje : public CosaConMovimiento{
protected:
	ContactListener *listenerTouchingGround;
public:
	Personaje();
	virtual ~Personaje();

	void setEntityIndex(int index);

	void moveLeft(bool isButtonDown);
	void moveRight(bool isButtonDown);
	void jump();

	virtual int getCurrentAnimation();

	b2Vec2 * getPosition();

	int getIndex();

	ContactListener* getListenerTouchingGround();
	void setListenerTouchingGround(ContactListener *aListener);
	bool isOnAir(); //se sobreescribe la de CosaConMovimiento para agregar el listener

	void update();
/*
	Animation * getAnimation(Resources * resources);
	*/
private:
	int userIndex;
};

#endif /* PERSONAJE_H_ */
