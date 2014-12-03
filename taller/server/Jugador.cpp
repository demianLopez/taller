#include "Jugador.h"
#include <math.h>
#include <iostream>
#include "../common/Message.h"
#include "../common/CommandCode.h"
#include "Data.h"
#include "Enemigo.h"
// Inicializa Jugador.
Jugador::Jugador(Client_handler * client, char * name) {
	this->client = client;
	this->name = name;
	this->body = NULL;
	this->tipoDeObjeto = 2; // Para los contactos. Los jugadores tienen valor
	this->keyRequestSend = 0;
	this->lives = 5;
	this->score = 0;
	this->isReady = false;
	this->invulnerable = false;
	shootRealized = 0;
	this->enemy = NULL;
}

void Jugador::enableSuperSpeed(){
	this->superSpeed = true;
	this->superSpeedTime = 10;
}

void Jugador::updateOnClientUserStats(){
	Message m;
	m.addCommandCode(UPDATE_PLAYER_STAT);
	m.addChar(this->lives);
	m.addChar(this->score);
	m.addEndChar();

	this->client->send_message(&m);
}

void Jugador::touchingEnemy(Enemigo * enemy){
	this->enemy = enemy;
}

int Jugador::getPlayerLives(){
	return this->lives;
}

int Jugador::getPlayerScore(){
	return this->score;
}

char * Jugador::getName() {
	return this->name;
}

void Jugador::setClient(Client_handler * client) {
	this->client = client;
}

void Jugador::addKeyCode(KeyCode keyCode) {
	this->keyCode.push_back(keyCode);
}

char * Jugador::getPlayerName() {
	return this->name;
}

void Jugador::setOffline(bool isOffline) {
	if (body)
		body->SetActive(!isOffline);
	this->offline = isOffline;
}

bool Jugador::isOffline() {
	return offline;
}

void Jugador::shoot(){
	if(this->enemy != NULL){
		enemy->tryKick(this);
	}
	if(this->shootRealized < 10){
		this->shootRealized++;
		Data::world->playerShooting(this);
	}
}

void Jugador::apllyCodes() {
	for (auto code : keyCode) {
		switch (code) {
		case MOVE_LEFT_DOWN:
			this->setMovingLeft(true);
			break;
		case MOVE_RIGHT_DOWN:
			this->setMovingRight(true);
			break;
		case MOVE_LEFT_UP:
			this->setMovingLeft(false);
			break;
		case MOVE_RIGHT_UP:
			this->setMovingRight(false);
			break;
		case JUMP:
			this->jump();
			break;
		case SPACE:
			this->shoot();
			break;
		}
	}

	keyCode.clear();
}

Jugador *  Jugador::clonePlayer() {
	Jugador * newPlayer = new Jugador(this->client, this->name);
	newPlayer->setOffline(this->isOffline());
	return newPlayer;
}

void Jugador::decreaseShoot(){
    	this->shootRealized --;
}

void Jugador::deadEvent(){
	this->body->SetActive(false);

	Message m;
	m.addCommandCode(SHOW_MESSAGE);
	string pM("");
	pM.append(this->getName());
	pM.append(" ha muerto");
	m.addCharArray(pM.c_str(), pM.size());
	m.addEndChar();

	Data::world->sendToWorldPlayers(&m);


	Message p;
	p.addCommandCode(ACTIVE_ENTITY);
	p.addChar(this->getIndex());
	p.addChar(false);
	p.addEndChar();

	Data::world->sendToWorldPlayers(&p);

	Jugador * toSpectate = Data::world->getFirstAlive();

	if(toSpectate == NULL){
		return;
	}

	Message c;
	c.addCommandCode(LOCK_CAMERA_ENTITY);
	c.addChar(toSpectate->getIndex());
	c.addEndChar();

	toSpectate->addSpectingMe(this);

	for(auto * p : mySpector){

		toSpectate->addSpectingMe(p);
		if(!p->isOffline()){
			p->getClient()->send_message(&c);
		}
	}

	this->client->send_message(&c);

}

bool Jugador::isInvulnerable(){
	return this->invulnerable;
}

bool Jugador::isDead(){
	return (this->lives == 0);
}

void Jugador::checkStatus() {
	if(invulnerable){
		//b2Vec2 pos(10, 10);
		//this->body->SetTransform(pos, 0);
		this->secondsInvulLeft--;
		if(secondsInvulLeft <= 0){
			this->invulnerable = false;
		}
	}

	if(superSpeed){
		this->superSpeedTime--;
		if(superSpeedTime <= 0){
			this->superSpeed = false;
		}
	}
}

Client_handler * Jugador::getClient() {
	return this->client;
}

void Jugador::addSpectingMe(Jugador * j){
	this->mySpector.push_back(j);
}

void Jugador::hit(){
	if(invulnerable || offline){
		return;
	}

	this->invulnerable = true;
	this->secondsInvulLeft = 3;

	this->lives--;
	this->updateOnClientUserStats();

	this->afterB2DEvent = 0;

	if(this->isDead()){
		this->afterB2DEvent = 1;
	}

	Data::world->addAfterChange(this);
}

void Jugador::change(){
	if(this->afterB2DEvent == 1){
		this->deadEvent();
	} else {

		int indx = this->getIndex();

		float posX = Data::world->getPlayerInitialPos(indx)->x;
		float posY = Data::world->getPlayerInitialPos(indx)->y;


		Message m;
		m.addCommandCode(FORCE_POSITION);
		m.addChar(indx);
		m.addFloat(&posX);
		m.addFloat(&posY);
		m.addChar(false);
		m.addEndChar();

		Data::world->sendToWorldPlayers(&m);

		Message c;
		c.addCommandCode(LOCK_CAMERA_ENTITY);
		c.addChar(indx);
		c.addEndChar();

		this->client->send_message(&c);

		this->body->SetTransform(b2Vec2(posX, posY), 0);
	}
}

void Jugador::evaluateAnimation() {
	if (this->mirandoParaLaDerecha) {
		if(this->superSpeed){
			currentAnimation = SUPER_RUN_RIGHT;
			return;
		}
		if (this->isOnAir() &&
		((this->getListenerTouchingGround()->getNumberOfContacts() == 0) ||
		  this->atravesandoRampa) ) {
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

	if(this->superSpeed){
		currentAnimation = SUPER_RUN_LEFT;
		return;
	}
	if (this->isOnAir() &&
	((this->getListenerTouchingGround()->getNumberOfContacts() == 0) ||
	  this->atravesandoRampa) ) {
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

