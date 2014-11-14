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
	void update(unsigned int delta);
	void addUpdateRequest(UpdateRequest * u, unsigned int currentTime);
	void initialize();

	void setAnimation(AnimationCode animation);
	void setOffline(bool offline);

	void setPlayerName(char * name);
private:
	AnimationCode animation;

	bool offline;

	int renderTimeCount;

	int * updateTimeArray;
	UpdateRequest ** updateRequestArray;
	int currentUpdate;
	int lastAddUpdate;

	char * pName;
	int lName;

	unsigned int lastUpdateTime;

	bool firstUpdate;

	VectorXY lastPosition;
	float lastRotation;
	VectorXY nextPosition;
};

#endif /* PLAYERENTITY_H_ */
