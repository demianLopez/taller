/*
 * Component.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "engine/GUI/Component.h"

Component::Component() {
	this->posX = 0;
	this->posY = 0;

	this->width = 0;
	this->height = 0;
}

void Component::setSize(int width, int height){
	this->width = width;
	this->height = height;
}

void Component::setPosition(int x, int y){
	this->posX = x;
	this->posY = y;
}

Component::~Component() {
	// TODO Auto-generated destructor stub
}

