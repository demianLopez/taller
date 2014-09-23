#include "CosaConMovimiento.h"

// Inicializa cosa quieta en (x,y), (0,0) por defecto.
CosaConMovimiento::CosaConMovimiento(b2World * gameWorld) {
	body = NULL; // DEBE SOBREESCRIBIRSE EN LA CLASE HIJA

	this->movingLeft = false;
	this->movingRight = false;

	this->stopAtHit = false;

	this->goingUp = false;
	this->goingDown = true;
	this->onTopJump = true;

	// Esto puede redefinirse en cada hijo, por defecto vale esto.
	this->movementSpeedX = MOVEMENT_SPEED_X_DEFAULT;
	this->movementSpeedY = MOVEMENT_SPEED_Y_DEFAULT;

	this->mirandoParaLaDerecha = true;
	this->wasMovingLeftFirst = false;
}

void CosaConMovimiento::setFreezeRotation(bool freezeRotation){
	this->body->SetFixedRotation(freezeRotation);
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
}

b2Body * CosaConMovimiento::getBody(){
	return this->body;
}

void CosaConMovimiento::setMovingLeft(bool isMovingLeft){
	if (isMovingLeft){	// Se quiere setear movingLeft true
		if ( !isMovingRight() ) wasMovingLeftFirst = true; // Se empezo a mover a la izq primero
	}else{	// Se quiere setear movingLeft false
		if ( isMovingRight() ) wasMovingLeftFirst = false; // De ahora en mas se empezo a mover a la der primero
	}
	movingLeft = isMovingLeft;	// seteo.
}

void CosaConMovimiento::setMovingRight(bool isMovingRight){
	// Para explicacion ver setMovingLeft()
	if (isMovingRight){
		if ( !isMovingLeft() ) wasMovingLeftFirst = false;
	}else{
		if ( isMovingLeft() ) wasMovingLeftFirst = true;
	}
	movingRight = isMovingRight;
}

bool CosaConMovimiento::isMovingLeft(){
	return movingLeft;
}

bool CosaConMovimiento::isMovingRight(){
	return movingRight;
}

bool CosaConMovimiento::isOnAir(){
	return (this->goingUp || this->goingDown || this->onTopJump);
}

Animation * CosaConMovimiento::getAnimation(Resources * resources){
	// FIXME: Mover esto a que sea definido por cada hijo de esta clase.
	if(this->isOnAir()){
		if(mirandoParaLaDerecha){
			return resources->getPlayerAirRight();
		} else {
			return resources->getPlayerAirLeft();
		}
	}


	if(mirandoParaLaDerecha){
		if(this->movingRight){
			return resources->getPlayerWalkRight();
		} else {
			return resources->getPlayerStaticRight();
		}
	} else {
		if(this->movingLeft){
			return resources->getPlayerWalkLeft();
		} else {
			return resources->getPlayerStaticLeft();
		}
	}


}

// Devuelve true si esta mirando para la derecha.
bool CosaConMovimiento::estaMirandoParaLaDerecha(){
	return mirandoParaLaDerecha;
}

void CosaConMovimiento::update(){
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	if(currentVel.y < 1 && currentVel.y > -1){ // Quieto en Y
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

	if(currentVel.y < -1){ // Cayendo
		if(this->onTopJump){
			this->onTopJump = false;
			this->goingDown = true;
		}
	}

	//Movimiento hacia los lados
	if (movingRight){
		if( !movingLeft || !wasMovingLeftFirst ){
			body->ApplyLinearImpulse(b2Vec2(15-body->GetLinearVelocity().x*2,0), body->GetWorldCenter(), true); //this->body->SetLinearVelocity(b2Vec2(movementSpeedX, currentVel.y));
			mirandoParaLaDerecha = true;
			return;
		}
	}
	if (movingLeft){
		if( !movingRight || wasMovingLeftFirst ){
			body->ApplyLinearImpulse(b2Vec2(-15-body->GetLinearVelocity().x*2,0), body->GetWorldCenter(), true); //this->body->SetLinearVelocity(b2Vec2(-movementSpeedX, currentVel.y));
			mirandoParaLaDerecha = false;
			return;
		}
	}

	stop(true,false);
}

CosaConMovimiento::~CosaConMovimiento(){

}
