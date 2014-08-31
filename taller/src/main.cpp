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

	pruebaEngine *pE = new pruebaEngine("Il");
	pE->setMaxFPS(50);
	pE->start();
	cout<<"Termino2";
	return 0;
}


