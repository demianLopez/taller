/*
 * main.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include <SDL2/SDL.h>
#include <iostream>
#include "pruebaEngine.h"
using namespace std;

int main(int argc, char *argv[]){

	pruebaEngine pE = pruebaEngine("Il");
	pE.setMaxFPS(50);
	pE.start();
	return 0;
}


