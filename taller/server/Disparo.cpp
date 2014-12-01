/*
 * Disparo.cpp
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#include <Disparo.h>

Disparo::Disparo(int index) {
	onUse = false;
	this->index = index;
}

bool Disparo::isOnUse(){
	return onUse;
}

int Disparo::getIndex(){
	return index;
}

Disparo::~Disparo() {
	// TODO Auto-generated destructor stub
}

