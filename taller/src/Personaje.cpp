#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"
#include "CosaConMovimiento.h"
#include <iostream>
Personaje::Personaje(b2World * gameWorld) : CosaConMovimiento(gameWorld){

}

void Personaje::jump(){
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	this->body->SetLinearVelocity(b2Vec2(currentVel.x, movementSpeedY));

	//body->ApplyLinearImpulse(b2Vec2(0,body->GetMass() * 8), body->GetWorldCenter(), true);
	//body->ApplyForceToCenter(b2Vec2(0,1006), true);
	this->goingUp = true;

}


Personaje::~Personaje(){
	//delete this->mainCharacterBody;
}




