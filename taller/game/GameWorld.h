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
#include "../common/polygons/Polygon.h"

class GameWorld {
public:
	GameWorld(VectorXY box2DWorldSize);

	void setScreenSize(VectorXY screenSize);

	std::vector<Polygon *> getPolygonList();

	void addPolygon(Polygon * polygon);

	VectorXY getBox2DWorldSize();


	virtual ~GameWorld();
private:
	VectorXY box2DSize;
	VectorXY screenSize;

	std::vector<Polygon *> polygonList;

};

#endif /* GAMEWORLD_H_ */
