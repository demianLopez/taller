/*
 * Disparo.h
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#ifndef DISPARO_H_
#define DISPARO_H_

#include <Box2D/Box2D.h>

class Disparo {
public:
	Disparo(int index);
	virtual ~Disparo();

	int getIndex();
	bool isOnUse();

	void setBox2DDefinitions(b2Body * body, b2Fixture * fixture);

	b2Vec2 * getPosition();
	float getRotation();

	void shoot(float pX, float pY, bool right);

	void setOnUse(bool onUse);
private:
	bool onUse;
	int index;

	b2Body * body;
	b2Fixture * fixture;
};

#endif /* DISPARO_H_ */
