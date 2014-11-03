#include "CosaConMovimiento.h"

float const TOLERANCIA_VELOCIDAD = 1;

CosaConMovimiento::CosaConMovimiento(){
	body = NULL; // DEBE SOBREESCRIBIRSE EN LA CLASE HIJA

	this->movingLeft = false;
	this->movingRight = false;

	this->stopAtHit = false;

	this->goingUp = false;
	this->goingDown = true;
	this->onTopJump = false;

	// Esto puede redefinirse en cada hijo, por defecto vale esto.
	this->movementSpeedX = MOVEMENT_SPEED_X_DEFAULT;
	this->movementSpeedY = MOVEMENT_SPEED_Y_DEFAULT;

	this->mirandoParaLaDerecha = true;
	this->wasMovingLeftFirst = false;

	this->lastVelocity = b2Vec2(0, 0);;
}

void CosaConMovimiento::setBox2DDefinitions(b2Body * body, b2Fixture * fixture){
	this->body = body;
	this->fixture = fixture;
}

bool CosaConMovimiento::isGoingUp() {
	return (this->body->GetLinearVelocity().y > TOLERANCIA_VELOCIDAD);
}

bool CosaConMovimiento::isGoingDown() {
	return (this->body->GetLinearVelocity().y < -TOLERANCIA_VELOCIDAD);
}

void CosaConMovimiento::update() {

}

void CosaConMovimiento::setFreezeRotation(bool freezeRotation) {
	this->body->SetFixedRotation(freezeRotation);
}

// Frena la cosa en X y/o Y
void CosaConMovimiento::stop(bool stopX, bool stopY) {
	b2Vec2 currentVel = this->body->GetLinearVelocity();
	if (stopX) {
		this->body->SetLinearVelocity(b2Vec2(0, currentVel.y));
	}
	if (stopY) {
		this->body->SetLinearVelocity(b2Vec2(currentVel.x, 0));
	}
}

b2Body * CosaConMovimiento::getBody() {
	return this->body;
}

void CosaConMovimiento::setMovingLeft(bool isMovingLeft) {
	if (isMovingLeft) {	// Se quiere setear movingLeft true
		if (!isMovingRight())
			wasMovingLeftFirst = true; // Se empezo a mover a la izq primero
	} else {	// Se quiere setear movingLeft false
		if (isMovingRight())
			wasMovingLeftFirst = false; // De ahora en mas se empezo a mover a la der primero
	}
	movingLeft = isMovingLeft;	// seteo.
}

void CosaConMovimiento::setMovingRight(bool isMovingRight) {
	// Para explicacion ver setMovingLeft()
	if (isMovingRight) {
		if (!isMovingLeft())
			wasMovingLeftFirst = false;
	} else {
		if (isMovingLeft())
			wasMovingLeftFirst = true;
	}
	movingRight = isMovingRight;
}

bool CosaConMovimiento::isMovingLeft() {
	return movingLeft;
}

bool CosaConMovimiento::isMovingRight() {
	return movingRight;
}

bool CosaConMovimiento::isOnAir() {
	return (this->goingUp || this->goingDown || this->onTopJump);
}

// Devuelve true si esta mirando para la derecha.
bool CosaConMovimiento::estaMirandoParaLaDerecha() {
	return mirandoParaLaDerecha;
}

Animation * CosaConMovimiento::getAnimation(Resources *resources) {
	return NULL;
}

CosaConMovimiento::~CosaConMovimiento() {

}
