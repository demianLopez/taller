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
#include <stdlib.h>
#include <iostream>

Enemigo::Enemigo(Move_pattern * movePattern) {
	this->movePattern = movePattern;
	this->dead = false;
	this->patron = 0;
}

bool Enemigo::isDead(){
	return this->dead;
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
		this->jump();
	} else if((eX - pX) < -1){
		this->setMovingLeft(false);
		this->setMovingRight(true);
		this->jump();
	} else {
		this->setMovingLeft(false);
		this->setMovingRight(false);
		this->jump();
	}
}

void Enemigo::movimientoLoco(){
	srand (time(NULL));
	int valor = rand() % 8 ;
	//if (valor == this->patron){
		//valor++;
	//}
	switch (valor){
		case 0:
			this->setMovingRight(false);
			this->setMovingLeft(true);
			this->jump();
			break;
		case 1:
			this->setMovingRight(true);
			this->setMovingLeft(false);
			this->jump();
			break;
		case 2:
			this->setMovingRight(false);
			this->setMovingLeft(false);
			this->jump();
			break;
		case 3:
			this->setMovingRight(true);
			this->setMovingLeft(false);
			break;
		case 4:
			this->setMovingRight(false);
			this->setMovingLeft(true);
			break;
		case 5:
			this->setMovingRight(true);
			this->setMovingLeft(false);
			break;
		case 6:
			this->setMovingRight(false);
			this->setMovingLeft(false);
			break;
		case 7:
			this->setMovingRight(false);
			this->setMovingLeft(true);
			break;
		default:
			this->setMovingRight(true);
			this->setMovingLeft(false);
			break;
	}
	this->patron = valor;
}

void Enemigo::colocar(int type, double posx, double posy) {
	this->type = type;
	this->posx = posx;
	this->posy = posy;
}
