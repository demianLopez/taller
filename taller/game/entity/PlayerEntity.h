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
	void render(Graphics * g);
	void update(UpdateRequest * u);
	void initialize();

	void setAnimation(int animation);
private:
	int animation;
};

#endif /* PLAYERENTITY_H_ */
