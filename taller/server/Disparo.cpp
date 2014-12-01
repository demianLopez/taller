/*
 * Disparo.cpp
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#include <Disparo.h>
#include "Data.h"

Disparo::Disparo(int index) {
	onUse = false;
	this->index = index;
}

void Disparo::setOnUse(bool onUse){
	this->onUse = onUse;
}


bool Disparo::isOnUse(){
	return onUse;
}

int Disparo::getIndex(){
	return index;
}

Disparo::~Disparo() {
	// TODO Auto-generated destructor stub
}

void Disparo::setBox2DDefinitions(b2Body* body, b2Fixture* fixture) {
	this->body = body;
	this->fixture = fixture;
}

void Disparo::destroy(){
	Data::world->addAfterChange(this);
}

void Disparo::change(){

	if(!this->onUse) { return; }
	this->body->SetActive(false);
	this->shootedBy->decreaseShoot();
	this->shootedBy = NULL;
	this->setOnUse(false);

	Message m;
	m.addCommandCode(ACTIVE_ENTITY);
	m.addChar(this->index);
	m.addChar(false);
	m.addEndChar();

	Data::world->sendToWorldPlayers(&m);

}

void Disparo::shoot(float pX, float pY, Jugador * shootedBy) {
	this->body->SetTransform(b2Vec2(pX, pY), 0);
	this->body->SetActive(true);

	this->shootedBy = shootedBy;

	if(shootedBy->estaMirandoParaLaDerecha()){
		body->ApplyLinearImpulse(b2Vec2(10, 0), body->GetWorldCenter(), true);
	} else {
		body->ApplyLinearImpulse(b2Vec2(-10, 0), body->GetWorldCenter(), true);
	}

	this->setOnUse(true);
}

b2Vec2* Disparo::getPosition() {
	return (b2Vec2*) &this->body->GetPosition();
}

float Disparo::getRotation() {
	return this->body->GetAngle();
}
