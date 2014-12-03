/*
 * Item.cpp
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#include <Item.h>
#include "../common/Message.h"
#include "Data.h"

Item::Item(int index) {
	this->index = index;
}

Item::~Item() {

}


void Item::putAt(float posX, float posY, int type){
	this->body->SetTransform(b2Vec2(posX, posY), 0);
	this->body->SetActive(true);
	this->type = type;
	this->onMap = true;

	Message m;
	m.addChar(PUT_BONUS);
	m.addChar(this->index);
	m.addFloat(&posX);
	m.addFloat(&posY);
	m.addChar(type);
	m.addEndChar();

	Data::world->sendToWorldPlayers(&m);
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
