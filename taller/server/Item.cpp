/*
 * Item.cpp
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#include <Item.h>

Item::Item(int index) {
	this->index = index;
}

Item::~Item() {

}


int Item::getIndex() {
	return index;
}

bool Item::isOnMap() {
	return onMap;
}

void Item::setOnMap(bool onMap) {
	this->onMap = onMap;
}

void Item::setBox2DDefinitions(b2Body* body, b2Fixture* fixture) {
	this->body = body;
	this->fixture = fixture;
}
