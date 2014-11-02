/*
 * PolygonEntity.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef POLYGONENTITY_H_
#define POLYGONENTITY_H_

#include "GameEntity.h"
#include <vector>
#include <VectorXY.h>

using std::vector;

class PolygonEntity: public GameEntity {
public:
	PolygonEntity(int index);

	void render(Graphics * g);
	void addVertex(float x, float y);

	virtual ~PolygonEntity();
private:
	vector<VectorXY *> vList;
};

#endif /* POLYGONENTITY_H_ */

