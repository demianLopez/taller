/*
 * Disparo.cpp
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#include <Disparo.h>

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

void Disparo::shoot(float pX, float pY, bool right) {
	this->body->SetTransform(b2Vec2(pX, pY), 0);
	this->body->SetActive(true);

	if(right){
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
