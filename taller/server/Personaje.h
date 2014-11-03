#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"
#include "ContactListener.h"

#include <Box2D/Box2D.h>

// Personaje (tanto jugador como NPC).
class Animation;
class Resources;

class Personaje {
protected:
	//ContactListener *listenerTouchingGround;
public:
	Personaje();
	virtual ~Personaje();

	void setBox2DDefinitions(b2Body * body, b2Fixture * fixture);
	void setEntityIndex(int index);

	void moveLeft(bool isButtonDown);
	void moveRight(bool isButtonDown);
	void jump();

	virtual int getCurrentAnimation();

	b2Vec2 * getPosition();

	int getIndex();

	/*
	void jump();
	void setListenerTouchingGround(ContactListener *aListener);
	bool isOnAir(); //se sobreescribe la de CosaConMovimiento para agregar el listener

	Animation * getAnimation(Resources * resources);
	*/
private:
	b2Body * body;
	b2Fixture * fixture;

	int userIndex;
};

#endif /* PERSONAJE_H_ */
