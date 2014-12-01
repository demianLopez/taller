/*
 * Disparo.h
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#ifndef DISPARO_H_
#define DISPARO_H_

class Disparo {
public:
	Disparo(int index);
	virtual ~Disparo();

	int getIndex();
	bool isOnUse();
private:
	bool onUse;
	int index;
};

#endif /* DISPARO_H_ */
