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
#include "Data.h"

Enemigo::Enemigo(Move_pattern * movePattern) {
	this->movePattern = movePattern;
	this->dead = false;
	this->patron = 0;
	this->nivelNieve = 0;
	this->inmovil = false;
	this->pateado = false;
	this->timeInmovil = 0;
}

bool Enemigo::isDead(){
	return this->dead;
}

void Enemigo::tryKick(Jugador * kickerPlayer){
	if(this->nivelNieve == 4 && !pateado){
		pateado = true;
		this->snowBallTime = 3;
		this->posx = this->body->GetPosition().x;
		this->posy = this->body->GetPosition().y;
		float direction = posx - kickerPlayer->getPosition()->x;
		this->body->DestroyFixture(this->fixture);
		Data::world->getBox2DWorld()->DestroyBody(this->body);
		Data::world->initializeEnemySnowBall(this);
		this->activeUpdate = false;

		this->kickedBy = kickerPlayer;

		if(direction < 0){
			body->ApplyLinearImpulse(b2Vec2(-60, 0), body->GetWorldCenter(), true);
		} else {
			body->ApplyLinearImpulse(b2Vec2(60, 0), body->GetWorldCenter(), true);
		}
	}
}

bool Enemigo::kicked(){
	return pateado;
}

float Enemigo::getRotation(){
	if(pateado){
		return this->body->GetAngle();
	}

	return 0;
}

//esto se llama cada 1 segundo!
void Enemigo::checkStatus(){
	if(this->dead){
		return;
	}
	if(pateado){
		this->snowBallTime --;
		if(snowBallTime <= 0){
			this->destroyMiSnowBall();
		}
	}
	if(this->inmovil && !pateado){
		this->timeInmovil --;

		if(this->timeInmovil == 0){
			this->nivelNieve = 0;
			this->inmovil = false;
		}
	}
}

void Enemigo::hit() {
	this->timeInmovil = 5;
	this->nivelNieve ++;
	if(!inmovil){
		inmovil = true;

		this->setMovingLeft(false);
		this->setMovingRight(false);
	}

	if(nivelNieve > 4){
		nivelNieve = 4;
	}
}

bool Enemigo::isInmovil(){
	return this->inmovil;
}

void Enemigo::addEnemyToList(Enemigo * e){
	this->enemyContainer.push_back(e);
}

void Enemigo::evaluateAnimation() {
	if(this->inmovil){
		switch(nivelNieve){
			case 1:
				currentAnimation = SNOW_LEVEL_1;
				break;
			case 2:
				currentAnimation = SNOW_LEVEL_2;
				break;
			case 3:
				currentAnimation = SNOW_LEVEL_3;
				break;
			case 4:
				currentAnimation = SNOW_LEVEL_4;
		}
		return;
	}

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
	if(inmovil) {
		return;
	}

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

void Enemigo::destroyMiSnowBall(){
	this->body->SetActive(false);
	Message m;
	m.addCommandCode(ACTIVE_ENTITY);
	m.addChar(this->getIndex());
	m.addChar(false);
	m.addEndChar();

	Data::world->sendToWorldPlayers(&m);

	int enemyKill = this->enemyContainer.size() + 1;
	unsigned int points = enemyKill * 5;
	this->kickedBy->score += points;
	this->kickedBy->updateOnClientUserStats();
	this->deadEvent();
}

void Enemigo::golpeadoPorBola(Enemigo * e){
	Data::world->addAfterChange(this);
	e->addEnemyToList(this);
	this->deadEvent();
}

void Enemigo::deadEvent(){
	this->dead = true;
	Data::world->evaluateBonusCreation(this->body->GetPosition().x, this->body->GetPosition().y);
}

void Enemigo::change(){
	this->body->SetActive(false);
	Message m;
	m.addCommandCode(ACTIVE_ENTITY);
	m.addChar(this->getIndex());
	m.addChar(false);
	m.addEndChar();

	Data::world->sendToWorldPlayers(&m);
}

void Enemigo::movimientoLoco(){
	if(inmovil) {
		return;
	}
	srand (time(NULL) + posx);
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
