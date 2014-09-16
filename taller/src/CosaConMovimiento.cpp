#include "CosaConMovimiento.h"

// Inicializa cosa quieta en (x,y), (0,0) por defecto.
CosaConMovimiento::CosaConMovimiento(b2World * gameWorld) {
	body = NULL; // DEBE SOBREESCRIBIRSE EN LA CLASE HIJA

	this->stopAtHit = false;

	this->goingUp = false;
	this->goingDown = true;
	this->onTopJump = true;

	// Esto puede redefinirse en cada hijo, por defecto vale esto.
	this->movementSpeedX = MOVEMENT_SPEED_X_DEFAULT;
	this->movementSpeedY = MOVEMENT_SPEED_Y_DEFAULT;

	this->mirandoParaLaDerecha = true;
}


// Frena la cosa en X y/o Y
void CosaConMovimiento::stop(bool stopX, bool stopY){
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	if(stopX){
		this->body->SetLinearVelocity(b2Vec2(0, currentVel.y));
	}
	if(stopY){
		this->body->SetLinearVelocity(b2Vec2(currentVel.x, 0));
	}
	// TODO: ver que significaba esto, o que pretendia hacer la funcion.
	/*
	if((currentVel.y < 1 && currentVel.y > -1) && !this->isOnAir()){
		this->mainCharacterBody->SetLinearVelocity(b2Vec2(0, currentVel.y));
	} else {
		this->stopAtHit = true;
	}
	*/
}

b2Body * CosaConMovimiento::getBody(){
	return this->body;
}

void CosaConMovimiento::moveLeft(){
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	this->body->SetLinearVelocity(b2Vec2(-movementSpeedX, currentVel.y));
	mirandoParaLaDerecha = false;
}

void CosaConMovimiento::moveRight(){
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	this->body->SetLinearVelocity(b2Vec2(movementSpeedX, currentVel.y));
	mirandoParaLaDerecha = true;
}

bool CosaConMovimiento::isOnAir(){
	return (this->goingUp || this->goingDown || this->onTopJump);
}

void CosaConMovimiento::jump(){
	if(!this->isOnAir()){
		b2Vec2 currentVel = this->body->GetLinearVelocity();
		this->body->SetLinearVelocity(b2Vec2(currentVel.x, movementSpeedY));
		this->goingUp = true;
	}
}



Animation * CosaConMovimiento::getAnimation(Resources * resources){

	//FIXME: deprecated, demi borralo si te parece.
	/*
	if(this->mainCharacterBody->GetLinearVelocity().y < 0){
		//return resources->getPlayerAnimationLeft(); caida libre
	}

	if(this->mainCharacterBody->GetLinearVelocity().x < 0){
		return resources->getPlayerAnimationLeft();
	}

	if(this->mainCharacterBody->GetLinearVelocity().x > 0){
		return resources->getPlayerAnimationRight();
	}
	*/

	if(mirandoParaLaDerecha){
		return resources->getPlayerAnimationRight();
	}
	//else: Esta mirando para la izquierda
	return resources->getPlayerAnimationLeft();
}

// Devuelve true si esta mirando para la derecha.
bool CosaConMovimiento::estaMirandoParaLaDerecha(){
	return mirandoParaLaDerecha;
}

void CosaConMovimiento::update(){
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	if(currentVel.y < 1 && currentVel.y > -1){
		if(this->goingUp){
			this->goingUp = false;
			this->onTopJump = true;
		}

		if(this->goingDown){
			this->goingDown = false;
			if(stopAtHit){
				this->stop();
				this->stopAtHit = false;
			}
		}

	}

	if(currentVel.y < -1){
		if(this->onTopJump){
			this->onTopJump = false;
			this->goingDown = true;
		}
	}
}

CosaConMovimiento::~CosaConMovimiento(){

}
