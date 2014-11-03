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
		case MOVE_LEFT_DOWN:
			this->moveLeft(true);
			break;
		case MOVE_RIGHT_DOWN:
			this->moveRight(true);
			break;
		case MOVE_LEFT_UP:
			this->moveLeft(false);
			break;
		case MOVE_RIGHT_UP:
			this->moveRight(false);
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


