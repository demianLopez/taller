/*
 * Enemigo.cpp
 *
 *  Created on: 29/11/2014
 *      Author: demian
 */

#include "Enemigo.h"

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

#include "../common/CommandCode.h"
#include "ContactListener.h"

Enemigo::Enemigo(Move_pattern * movePattern) {
	this->movePattern = movePattern;
}

void Enemigo::hit() {
}

void Enemigo::evaluateAnimation() {
	if (this->mirandoParaLaDerecha) {
		if (this->isOnAir()
				&& this->getListenerTouchingGround()->getNumberOfContacts()
						== 0) {
			currentAnimation = A_JUMP_RIGHT;
			return;
		}

		if (this->isMovingRight()) {
			currentAnimation = A_WALK_RIGHT;
			return;
		}

		currentAnimation = A_STAND_RIGHT;
		return;
	}

	if (this->isOnAir()
			&& this->getListenerTouchingGround()->getNumberOfContacts() == 0) {
		currentAnimation = A_JUMP_LEFT;
		return;
	}

	if (this->isMovingLeft()) {
		currentAnimation = A_WALK_LEFT;
		return;
	}

	currentAnimation = A_STAND_LEFT;
	return;

}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

void Enemigo::evaluateMovement(Jugador* nearPlayer) {
	float eX = this->body->GetPosition().x;
	float pX = nearPlayer->getPosition()->x;

	if((eX - pX) > 1){
		this->setMovingRight(false);
		this->setMovingLeft(true);
	} else if((eX - pX) < -1){
		this->setMovingLeft(false);
		this->setMovingRight(true);
	} else {
		this->setMovingLeft(false);
		this->setMovingRight(false);
	}
}
