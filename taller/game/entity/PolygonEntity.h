/*
 * PolygonEntity.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef POLYGONENTITY_H_
#define POLYGONENTITY_H_

#include "MovementEntity.h"
#include <vector>
#include <VectorXY.h>
#include <engine/Image.h>

using std::vector;

class PolygonEntity: public MovementEntity {
public:
	PolygonEntity(int index);

	void render(Graphics * g, unsigned int delta);
	void initialize();
	void applyUpdate(UpdateRequest * u);

	void addVertex(float x, float y);


	void setStatic(bool isStatic);

	void buildRectangle(short int * vX, short int * vY);

	virtual ~PolygonEntity();
private:
	vector<VectorXY *> vList;
	Image * polygonImage;

	bool isStatic;
};

#endif /* POLYGONENTITY_H_ */

