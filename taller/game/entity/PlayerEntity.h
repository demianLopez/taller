/*
 * PlayerEntity.h
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#ifndef PLAYERENTITY_H_
#define PLAYERENTITY_H_

#include "MovementEntity.h"


class PlayerEntity: public MovementEntity {
public:
	PlayerEntity(int index);
	virtual ~PlayerEntity();
	void render(Graphics * g, unsigned int delta);
	void initialize();
	void applyUpdate(UpdateRequest * u);

	void setAnimation(AnimationCode animation);
	void setOffline(bool offline);

	void setPlayerName(char * name);
private:
	AnimationCode animation;
	bool offline;

	char * pName;
	int lName;
};

#endif /* PLAYERENTITY_H_ */
