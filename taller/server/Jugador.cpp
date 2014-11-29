#include "Jugador.h"
#include <math.h>
#include <iostream>
#include "../common/Message.h"
#include "../common/CommandCode.h"

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
}

void Jugador::updateOnClientUserStats(){
	Message m;
	m.addCommandCode(UPDATE_PLAYER_STAT);
	m.addChar(this->lives);
	m.addChar(this->score);
	m.addEndChar();

	this->client->send_message(&m);
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
		}
	}

	keyCode.clear();
}

Jugador *  Jugador::clonePlayer() {
	Jugador * newPlayer = new Jugador(this->client, this->name);
	newPlayer->setOffline(this->isOffline());
	return newPlayer;
}

Client_handler * Jugador::getClient() {
	return this->client;
}

void Jugador::evaluateAnimation() {
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

