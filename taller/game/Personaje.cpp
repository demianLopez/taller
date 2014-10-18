#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"
#include "CosaConMovimiento.h"
#include <iostream>
Personaje::Personaje(b2World * gameWorld) :
		CosaConMovimiento(gameWorld) {
	listenerTouchingGround = NULL;
}

void Personaje::jump() {
	if (listenerTouchingGround->getNumberOfContacts() == 0)
		return; //Esto medio que esta repetido, ya se checkea en SnowBross.
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	this->body->SetLinearVelocity(b2Vec2(currentVel.x, movementSpeedY));

	//body->ApplyLinearImpulse(b2Vec2(0,body->GetMass() * 8), body->GetWorldCenter(), true);
	//body->ApplyForceToCenter(b2Vec2(0,1006), true);
	this->goingUp = true;

}

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

Personaje::~Personaje() {
	//delete this->mainCharacterBody;
}

