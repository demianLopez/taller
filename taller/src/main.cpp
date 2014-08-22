/*
 * main.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "SDL.h"
#include <iostream>
#include "pruebaEngine.h"
using namespace std;

int main(int argc, char *argv[]){

	pruebaEngine *pE = new pruebaEngine("Juego prueba");
	pE->start();
	cout<<"Termino";
	return 0;
}


