/*
 * PlayerEntity.h
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#ifndef PLAYERENTITY_H_
#define PLAYERENTITY_H_

#include "GameEntity.h"

class PlayerEntity: public GameEntity {
public:
	PlayerEntity(int index);
	virtual ~PlayerEntity();
	void render(Graphics * g, unsigned int delta);
	void update(UpdateRequest * u, unsigned int elapsedTime);
	void initialize();

	void setAnimation(AnimationCode animation);
	void setOffline(bool offline);
private:
	AnimationCode animation;

	bool offline;

	int elapsedTime;
	int lastUpdateTime;

	int renderTimeCount;


	VectorXY lastPosition;
	float lastRotation;
	VectorXY nextPosition;
};

#endif /* PLAYERENTITY_H_ */
