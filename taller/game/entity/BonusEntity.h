/*
 * BonusEntity.h
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#ifndef BONUSENTITY_H_
#define BONUSENTITY_H_

#include "GameEntity.h"

class BonusEntity: public GameEntity {
public:
	BonusEntity(int index);

	void render(Graphics * g, unsigned int dela);
	void update(unsigned int delta);
	void addUpdateRequest(UpdateRequest * u,
			unsigned int currentTime);
	void initialize();

	void putAt(float posX, float posY, int bonusType);


	virtual ~BonusEntity();
private:
	int type;
	float posX;
	float posY;
};

#endif /* BONUSENTITY_H_ */
