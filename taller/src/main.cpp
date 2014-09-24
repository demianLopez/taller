#include "SDL.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "SnowBross.h"
#include "Jugador.h"
#include "LectorJson.h"
using namespace std;
	int main(int argc, char *argv[]){

	//LectorJson* lector = new LectorJson();
	//lector->cargarEscenario("asf");
	//delete lector;

	SnowBross *pE = new SnowBross("Snow Bross");
	//pruebaEngine *pE = new pruebaEngine("Il");
	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();
	return 0;
}
