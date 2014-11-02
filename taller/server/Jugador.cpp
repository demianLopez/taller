#include "Jugador.h"
#include <math.h>
#include <iostream>

// Inicializa Jugador.
Jugador::Jugador(Client_handler * client, char * name){
	this->client = client;
	this->userIndex = client->userIndex;
	this->name = name;
}

char * Jugador::getName(){
	return this->name;
}

int Jugador::getIndex(){
	return userIndex;
}

Client_handler * Jugador::getClient(){
	return this->client;
}


