/*
 * Component.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "Component.h"

Component::Component() {
	this->posX = 0;
	this->posY = 0;

	this->width = 0;
	this->height = 0;
}

void Component::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

bool Component::isClicked(int xClick, int yClick) {
	bool hoverX = xClick > posX && xClick < (posX + width);
	bool hoverY = yClick > posY && yClick < (posY + height);

	return hoverX && hoverY;
}

void Component::setPosition(int x, int y) {
	this->posX = x;
	this->posY = y;
}

Component::~Component() {
}

