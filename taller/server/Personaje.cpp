#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"
#include "CosaConMovimiento.h"
#include <iostream>

Personaje::Personaje()  {
	listenerTouchingGround = NULL;
}

int Personaje::getIndex(){
	return userIndex;
}

int Personaje::getCurrentAnimation(){
	return 0;
}

void Personaje::moveLeft(bool isButtonDown){
	body->ApplyLinearImpulse(
			b2Vec2(-50 - body->GetLinearVelocity().x * 2, 0),
			body->GetWorldCenter(), true);

}

void Personaje::moveRight(bool isButtonDown){
	body->ApplyLinearImpulse(
			b2Vec2(50 - body->GetLinearVelocity().x * 2, 0),
			body->GetWorldCenter(), true);
}

ContactListener* Personaje::getListenerTouchingGround(){
	return listenerTouchingGround;
}

void Personaje::setListenerTouchingGround(ContactListener *aListener){
	listenerTouchingGround = aListener;
}

void Personaje::jump(){
	if(listenerTouchingGround->getNumberOfContacts() == 0) return; //Esto medio que esta repetido, ya se checkea en SnowBross.
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	this->body->SetLinearVelocity(b2Vec2(currentVel.x, movementSpeedY));

	//body->ApplyLinearImpulse(b2Vec2(0,body->GetMass() * 8), body->GetWorldCenter(), true);
	//body->ApplyForceToCenter(b2Vec2(0,1006), true);
	this->goingUp = true;
}

b2Vec2 * Personaje::getPosition(){
	return (b2Vec2*) &this->body->GetPosition();
}

void Personaje::setEntityIndex(int index){
	this->userIndex = index;
}

void Personaje::update() {
	cout << "cantidad de contactos: " << listenerTouchingGround->getNumberOfContacts() << endl;
	b2Vec2 currentVel = this->body->GetLinearVelocity();

	if (currentVel.y < 1 && currentVel.y > -1) { // Quieto en Y
		if (this->goingUp) {
			this->goingUp = false;
			this->onTopJump = true;
		}

		if (this->goingDown) {
			this->goingDown = false;
			if (stopAtHit) {
				this->stop();
				this->stopAtHit = false;
			}
		}

	}

	if (currentVel.y < -1) { // Cayendo
		if (this->onTopJump) {
			this->onTopJump = false;
			this->goingDown = true;
		}
	}

	//Movimiento hacia los lados
	if (movingRight) {
		if (!movingLeft || !wasMovingLeftFirst) {
			body->ApplyLinearImpulse(
					b2Vec2(25 - body->GetLinearVelocity().x * 2, 0),
					body->GetWorldCenter(), true); //this->body->SetLinearVelocity(b2Vec2(movementSpeedX, currentVel.y));
			mirandoParaLaDerecha = true;
			return;
		}
	}
	if (movingLeft) {
		if (!movingRight || wasMovingLeftFirst) {
			body->ApplyLinearImpulse(
					b2Vec2(-25 - body->GetLinearVelocity().x * 2, 0),
					body->GetWorldCenter(), true); //this->body->SetLinearVelocity(b2Vec2(-movementSpeedX, currentVel.y));
			mirandoParaLaDerecha = false;
			return;
		}
	}

	stop(true, false);
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

