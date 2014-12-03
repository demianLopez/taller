/*
 * Water.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: maxi
 */

#include <Water.h>

Water::Water(int index) {
	this->index = index;
}

int Water::getIndex(){
	return index;
}

VectorXY Water::getPosition(){
	return position;
}

void Water::setPosition(float x, float y, float width, float height) {
	this->position = VectorXY(x, y);
	this->size = VectorXY(width, height);
}

VectorXY Water::getSize(){
	return this->size;
}

Water::~Water() {
	// TODO Auto-generated destructor stub
}

