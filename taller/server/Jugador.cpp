#include "Jugador.h"
#include <math.h>
#include <iostream>

// Inicializa Jugador.
Jugador::Jugador(Client_handler * client, char * name){
	this->client = client;
	this->name = name;

	this->tipoDeObjeto = 2; // Para los contactos. Los jugadores tienen valor 2.
}

char * Jugador::getName(){
	return this->name;
}

void Jugador::addKeyCode(KeyCode keyCode){
	this->keyCode.push_back(keyCode);
}

void Jugador::setOffline(bool isOffline){
	this->offline = isOffline;
}

bool Jugador::isOffline(){
	return offline;
}

void Jugador::apllyCodes(){
	for(auto code : keyCode){
		switch(code)
		{
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


Client_handler * Jugador::getClient(){
	return this->client;
}


