/*
 * Disparo.h
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#ifndef DISPARO_H_
#define DISPARO_H_

#include <Box2D/Box2D.h>
#include "Jugador.h"
#include "B2DAfterChange.h"

class Disparo : public B2DAfterChange{
public:
	Disparo(int index);
	virtual ~Disparo();

	int getIndex();
	bool isOnUse();
	void destroy();

	void change();

	void setBox2DDefinitions(b2Body * body, b2Fixture * fixture);

	b2Vec2 * getPosition();
	float getRotation();

	void shoot(float pX, float pY, Jugador * shootedBy);

	void setOnUse(bool onUse);
private:
	bool onUse;
	int index;

	b2Body * body;
	b2Fixture * fixture;

	Jugador * shootedBy;
};

#endif /* DISPARO_H_ */
