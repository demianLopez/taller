/*
 * ContactContainer.h
 *
 *  Created on: Nov 3, 2014
 *      Author: maxi
 */

#ifndef SERVER_CONTACTCONTAINER_H_
#define SERVER_CONTACTCONTAINER_H_

class ContactContainer {
public:
	static const int POLYGON = 1;
	static const int JUGADOR = 2;
	static const int SENSORDELPIE = 3;
	static const int ENEMY = 4;
	static const int SENSORDELACABEZA = 5;
	static const int DISPARO_JUGADOR = 6;
	static const int SNOW_BALL_ENEMY = 7;
	static const int BONUS = 8;
	static const int DISPARO_ENEMIGO = 9;
	static const int AGUA = 10;

	int type;
	void *containedThing;

	ContactContainer(int typeOfThing, void *contained);
};

#endif /* SERVER_CONTACTCONTAINER_H_ */
