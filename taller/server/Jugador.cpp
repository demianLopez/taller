#include "Jugador.h"
#include <math.h>
#include <iostream>

// Inicializa Jugador.
Jugador::Jugador(int userIndex, char * name){
	this->userIndex = userIndex;
	this->name = name;
}

char * Jugador::getName(){
	return this->name;
}

int Jugador::getIndex(){
	return userIndex;
}


