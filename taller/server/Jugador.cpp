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

Client_handler * Jugador::getClient(){
	return this->client;
}


