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
	this->onMap = false;
	this->playerAfected = NULL;
	this->fixture = NULL;
	this->body = NULL;
	this->type = 0;
}

Item::~Item() {

}

void Item::change(){
	if(!this->onMap){
		return;
	}
	this->body->SetActive(false);
	this->onMap = false;

	switch(type){
		case 0:
			playerAfected->score += 2;
			playerAfected->updateOnClientUserStats();
			break;
		case 1:
			playerAfected->score += 4;
			playerAfected->updateOnClientUserStats();
			break;
		case 2:
			playerAfected->enableSuperSpeed();
			break;
		case 3:
			if(playerAfected->lives == 5){
				playerAfected->score += 5;
			} else {
				playerAfected->lives ++;
			}
			playerAfected->updateOnClientUserStats();
			break;
	}

	this->playerAfected = NULL;

	Message m;
	m.addCommandCode(ACTIVE_ENTITY);
	m.addChar(this->index);
	m.addChar(false);
	m.addEndChar();

	Data::world->sendToWorldPlayers(&m);
}

void Item::consumir(Jugador * player){
	Data::world->addAfterChange(this);
	this->playerAfected = player;
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
