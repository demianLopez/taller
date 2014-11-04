#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "VectorXY.h"
#include "CosaConMovimiento.h"
#include "ContactListener.h"
#include <CommandCode.h>

#include <Box2D/Box2D.h>

// Personaje (tanto jugador como NPC).
class Animation;
class Resources;


class Personaje : public CosaConMovimiento{
protected:
	ContactListener *listenerTouchingGround;
	AnimationCode currentAnimation;
public:
	Personaje();
	virtual ~Personaje();

	void setEntityIndex(int index);

	void moveLeft(bool isButtonDown);
	void moveRight(bool isButtonDown);
	void jump();

	AnimationCode getCurrentAnimation();

	b2Vec2 * getPosition();

	int getIndex();

	ContactListener* getListenerTouchingGround();
	void setListenerTouchingGround(ContactListener *aListener);

	void update();
/*
	Animation * getAnimation(Resources * resources);
	*/
private:


	virtual void evaluateAnimation();

	int userIndex;
};

#endif /* PERSONAJE_H_ */
