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
class GameEntity;
#include <UpdateRequest.h>
#include <mutex>

class GameWorld {
public:
	GameWorld(float tX, float tY);

	void setScreenSize(VectorXY screenSize);

	std::vector<GameEntity *> getEntityList();

	void addEntity(GameEntity * entity);

	VectorXY getBox2DWorldSize();

	void generateGraphics();

	VectorXY box2DToSDLSize(VectorXY * box2DCoord);
	VectorXY box2DToSDL(VectorXY * box2DCoord);

	void addUpdateRequest(UpdateRequest * update);

	void update();

	virtual ~GameWorld();
private:
	VectorXY box2DSize;
	VectorXY screenSize;

	std::vector<GameEntity *> entityList;

	std::vector<UpdateRequest *> updatesList;

	std::mutex updateMutex;

};

#endif /* GAMEWORLD_H_ */
