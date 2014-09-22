#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"
#include "CosaConMovimiento.h"

Personaje::Personaje(b2World * gameWorld) : CosaConMovimiento(gameWorld){

}

void Personaje::jump(){
	if(!this->isOnAir()){
		b2Vec2 currentVel = this->body->GetLinearVelocity();
		this->body->SetLinearVelocity(b2Vec2(currentVel.x, movementSpeedY));
		this->goingUp = true;
	}
}

Personaje::~Personaje(){
	//delete this->mainCharacterBody;
}




