/*
 * MovementEntity.h
 *
 *  Created on: 23/11/2014
 *      Author: demian
 */

#ifndef MOVEMENTENTITY_H_
#define MOVEMENTENTITY_H_

#include <queue>

#include "../../common/UpdateRequest.h"
#include "../VectorXY.h"
#include "GameEntity.h"

class MovementEntity: public GameEntity {
public:
	MovementEntity(int index);
	void update(unsigned int delta);
	void addUpdateRequest(UpdateRequest * u, unsigned int currentTime);

	void setAnimation(AnimationCode animation);

	virtual void applyUpdate(UpdateRequest * u) = 0;
	void setUpdateable(bool updateable);

	virtual ~MovementEntity();
private:
	void setedActive(bool active);

	std::queue<int> updateTime;
	std::queue<UpdateRequest *> updateRequest;

	VectorXY lastPosition;
	VectorXY nextPosition;

	float lastRotation;
	float nextRotation;

	unsigned int lastUpdateTime;
	bool firstUpdate;
	int renderTimeCount;

	int difTime;
	bool updateable;
protected:
	AnimationCode animation;
};

#endif /* MOVEMENTENTITY_H_ */
