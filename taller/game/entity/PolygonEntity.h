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
#include <engine/Image.h>

using std::vector;

class PolygonEntity: public GameEntity {
public:
	PolygonEntity(int index);

	void render(Graphics * g, unsigned int delta);
	void initialize();
	void addVertex(float x, float y);

	void update(UpdateRequest * u,  unsigned int elapsedTime);
	void setStatic(bool isStatic);



	virtual ~PolygonEntity();
private:
	vector<VectorXY *> vList;
	Image * polygonImage;

	bool isStatic;

	int elapsedTime;
	int lastUpdateTime;

	int renderTimeCount;



	VectorXY lastPosition;
	VectorXY nextPosition;
	float lastRotation;
};

#endif /* POLYGONENTITY_H_ */

