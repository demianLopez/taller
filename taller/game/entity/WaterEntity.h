/*
 * WaterEntity.h
 *
 *  Created on: Dec 3, 2014
 *      Author: maxi
 */

#ifndef GAME_ENTITY_WATERENTITY_H_
#define GAME_ENTITY_WATERENTITY_H_

#include "GameEntity.h"
#include "../engine/Image.h"
#include "../VectorXY.h"
#include "../GameWorld.h"

class WaterEntity : public GameEntity {
public:
	WaterEntity(int index);
	virtual ~WaterEntity();

	void render(Graphics * g, unsigned int dela);
	void update(unsigned int delta);
	void addUpdateRequest(UpdateRequest * u, unsigned int currentTime);
	void initialize();

	//bool isActive();

	//void setRotation(float rotation);

	//void setWorld(GameWorld * gameWorld);
	//void setPosition(float x, float y);
	//VectorXY getPosition();


	Image * waterImage;
};

#endif /* GAME_ENTITY_WATERENTITY_H_ */
