#include "Jugador.h"
#include <math.h>
#include <iostream>

// Inicializa Jugador.
Jugador::Jugador(Client_handler * client, char * name){
	this->client = client;
	this->name = name;
}

char * Jugador::getName(){
	return this->name;
}

void Jugador::addKeyCode(KeyCode keyCode){
	this->keyCode.push_back(keyCode);
}

void Jugador::apllyCodes(){
	for(auto code : keyCode){
		switch(code)
		{
		case MOVE_LEFT:
			this->moveLeft();
			break;
		case MOVE_RIGHT:
			this->moveRight();
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


