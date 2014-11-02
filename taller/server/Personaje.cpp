#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"
#include "CosaConMovimiento.h"
#include <iostream>

Personaje::Personaje()  {
	//listenerTouchingGround = NULL;
}

void Personaje::setBox2DDefinitions(b2Body * body, b2Fixture * fixture){
	this->body = body;
	this->fixture = fixture;
}

int Personaje::getIndex(){
	return userIndex;
}

int Personaje::getCurrentAnimation(){
	return 0;
}

void Personaje::moveLeft(){
	body->ApplyLinearImpulse(
			b2Vec2(-15 - body->GetLinearVelocity().x * 2, 0),
			body->GetWorldCenter(), true);

}

void Personaje::moveRight(){
	body->ApplyLinearImpulse(
			b2Vec2(15 - body->GetLinearVelocity().x * 2, 0),
			body->GetWorldCenter(), true);
}

void Personaje::jump(){
	body->ApplyLinearImpulse(b2Vec2(0,body->GetMass() * 8), body->GetWorldCenter(), true);
}

b2Vec2 * Personaje::getPosition(){
	return (b2Vec2*) &this->body->GetPosition();
}

void Personaje::setEntityIndex(int index){
	this->userIndex = index;
}
/*
void Personaje::jump() {

	if (listenerTouchingGround->getNumberOfContacts() == 0)
		return; //Esto medio que esta repetido, ya se checkea en SnowBross.
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	this->body->SetLinearVelocity(b2Vec2(currentVel.x, movementSpeedY));

	//body->ApplyLinearImpulse(b2Vec2(0,body->GetMass() * 8), body->GetWorldCenter(), true);
	//body->ApplyForceToCenter(b2Vec2(0,1006), true);
	this->goingUp = true;


}

/*
void Personaje::setListenerTouchingGround(ContactListener *aListener) {
	listenerTouchingGround = aListener;
}

bool Personaje::isOnAir() {
	return (listenerTouchingGround->getNumberOfContacts() == 0);
}

Animation * Personaje::getAnimation(Resources * resources) {
	if (this->isOnAir()) {
		if (mirandoParaLaDerecha) {
			return resources->getPlayerAirRight();
		} else {
			return resources->getPlayerAirLeft();
		}
	}

	if (mirandoParaLaDerecha) {
		if (this->movingRight) {
			return resources->getPlayerWalkRight();
		} else {
			return resources->getPlayerStaticRight();
		}
	} else {
		if (this->movingLeft) {
			return resources->getPlayerWalkLeft();
		} else {
			return resources->getPlayerStaticLeft();
		}
	}
}

*/

Personaje::~Personaje() {
	//delete this->mainCharacterBody;
}

