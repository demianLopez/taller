/*
 * Water.h
 *
 *  Created on: Dec 3, 2014
 *      Author: maxi
 */

#ifndef SERVER_WATER_H_
#define SERVER_WATER_H_

#include "VectorXY.h"

class Water {
public:
	Water(int index);
	virtual ~Water();

	int getIndex();
	VectorXY getPosition();

	void setPosition(float x, float y);

private:
	int index;
	VectorXY position;
};

#endif /* SERVER_WATER_H_ */
