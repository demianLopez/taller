#include "SDL.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "SnowBross.h"
#include "Jugador.h"
#include "LectorJson.h"
#include "../common/Logger.h"
#include "engine/game.h"

using namespace std;

int main(int argc, char *argv[]){
	bool continues = true;
	while(continues){
		Logger::initializeCustomLogs();

		LectorJson* lector = new LectorJson();
		lector->cargarEscenario("Resources/tp0.json");
		GestorEscenario * gE = lector->obtenerGestorEscenario();

		SnowBross *pE = new SnowBross("Snow Bross");
		pE->setScreenSize(gE->datos().anchopx, gE->datos().altopx);
		pE->instantiate();
		pE->setWorld(gE->obtenerMundo());

		delete lector;

		pE->setMaxFPS(50);
		pE->showFPS(true);
		continues = pE->start();
		delete pE;
		//delete lector; //estamos perdiendo memoria con esto, pero falla si lo descomento..
	}
	return 0;
}
