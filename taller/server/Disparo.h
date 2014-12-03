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
#include "Enemigo.h"

class Disparo : public B2DAfterChange{
public:
	Disparo(int index);
	virtual ~Disparo();

	int getIndex();
	bool isOnUse();
	void destroy();

	void checkStatus();

	void change();

	void setBox2DDefinitions(b2Body * body, b2Fixture * fixture);

	b2Vec2 * getPosition();
	float getRotation();

	void shoot(float pX, float pY, Jugador * shootedBy);
	void enemyShoot(float pX, float pY, Enemigo * shootedBy);

	void setOnUse(bool onUse);
private:
	bool onUse;
	int index;

	b2Body * body;
	b2Fixture * fixture;

	Jugador * shootedBy;
	Enemigo * enemyShotedBy;

	bool enemyShooted;

	int lifeTime;
};

#endif /* DISPARO_H_ */
