/*
 * PolygonEntity.cpp
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#include "PolygonEntity.h"

PolygonEntity::PolygonEntity(int index) :
		GameEntity(index) {
	// TODO Auto-generated constructor stub

}

void PolygonEntity::render(Graphics * g) {

}

void PolygonEntity::addVertex(float x, float y) {
	this->vList.push_back(new VectorXY(x, y));
}

PolygonEntity::~PolygonEntity() {
	for (auto * v : vList) {
		delete v;
	}
}

