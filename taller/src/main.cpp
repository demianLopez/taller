/*
 * main.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */


#include "SDL.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "SnowBross.h"
#include "Jugador.h"
#include "LectorJsonTest.h"
#include "engine/Logger.h"

using namespace std;


int main(int argc, char *argv[]){
	/*
	LectorJsonTest* lector = new LectorJsonTest();

	lector->imprimirXConsola();
	delete lector;
	*/

	Logger::initializeCustomLogs();

	SnowBross *pE = new SnowBross("Snow Bross");
	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();
	return 0;

}
