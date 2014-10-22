#include <iostream>
#include <stdio.h>
#include "SnowBross.h"
#include "Jugador.h"
#include "engine/Game.h"
#include "../common/Logger.h"
#include "MainMenu.h"
#include "LevelState.h"

using namespace std;

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 600;

int main(int argc, char *argv[]){
	Logger::initializeCustomLogs();

	SnowBross *pE = new SnowBross("Snow Bross");
	pE->setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	pE->instantiate();

	//TODO: World ahora se tiene que venir via internet, alguien lo tiene que generar!
	//pE->setWorld(gE->obtenerMundo());
	//delete lector;

	pE->addState(new MainMenu());
	LevelState * lS = new LevelState();
	lS->setWorld(new GameWorld(VectorXY(50, 30)));

	pE->addState(lS);
	pE->enterState(0);

	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();

		//delete lector; //estamos perdiendo memoria con esto, pero falla si lo descomento..

	return 0;
}
