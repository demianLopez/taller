#include "SDL.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "SnowBross.h"
#include "Jugador.h"
#include "LectorJson.h"
using namespace std;
	int main(int argc, char *argv[]){

	LectorJson* lector = new LectorJson();
	lector->cargarEscenario("asf");
	GestorEscenario * gE = lector->obtenerGestorEscenario();

	SnowBross *pE = new SnowBross("Snow Bross");
	pE->setScreenSize(gE->datos().anchopx, gE->datos().altopx);
	pE->instantiate();
	pE->setWorld(gE->obtenerMundo());

	delete lector;

	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();
	return 0;
}
