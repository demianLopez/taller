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
	if (isMovingLeft){
		if ( !isMovingRight() ) wasMovingLeftFirst = true;
	}else{
		if ( isMovingRight() ) wasMovingLeftFirst = false;
	}
	movingLeft = isMovingLeft;
}

void CosaConMovimiento::setMovingRight(bool isMovingRight){
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
			this->body->SetLinearVelocity(b2Vec2(movementSpeedX, currentVel.y));
			mirandoParaLaDerecha = true;
			return;
		}
	}
	if (movingLeft){
		if( !movingRight || wasMovingLeftFirst ){
			this->body->SetLinearVelocity(b2Vec2(-movementSpeedX, currentVel.y));
			mirandoParaLaDerecha = false;
			return;
		}
	}

	stop(true,false);
/*
	if(movingLeft){
		this->body->SetLinearVelocity(b2Vec2(-movementSpeedX, currentVel.y));
		mirandoParaLaDerecha = false;
	}else{
		if (movingRight){
			mirandoParaLaDerecha = true;
			this->body->SetLinearVelocity(b2Vec2(movementSpeedX, currentVel.y));
		}else{
			this->stop(true, false);
		}
	}
*/
}

CosaConMovimiento::~CosaConMovimiento(){

}
