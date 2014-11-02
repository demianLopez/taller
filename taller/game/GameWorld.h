/*
 * GameWorld.h
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "VectorXY.h"
#include <vector>
#include <entity/GameEntity.h>

class GameWorld {
public:
	GameWorld(float tX, float tY);

	void setScreenSize(VectorXY screenSize);

	std::vector<GameEntity *> getEntityList();

	void addEntity(GameEntity * entity);

	VectorXY getBox2DWorldSize();

	void generateGraphics();


	virtual ~GameWorld();
private:
	VectorXY box2DSize;
	VectorXY screenSize;

	std::vector<GameEntity *> entityList;

};

#endif /* GAMEWORLD_H_ */
