#include <iostream>
#include <stdio.h>
#include "SnowBross.h"
#include "Jugador.h"
#include "engine/Game.h"
#include "../common/Logger.h"


using namespace std;

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 600;

int mainServer(){
	std::cout<<"Server"<<endl;
	return 0;
}

int mainCliente(){
	Logger::initializeCustomLogs();

	SnowBross *pE = new SnowBross("Snow Bross");
	pE->setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	pE->instantiate();

	//TODO: World ahora se tiene que venir via internet, alguien lo tiene que generar!
	//pE->setWorld(gE->obtenerMundo());
	//delete lector;

	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();

		//delete lector; //estamos perdiendo memoria con esto, pero falla si lo descomento..

	return 0;
}

int main(int argc, char *argv[]){
	if(argc > 1){
		return mainServer();
	}

	return mainCliente();
}
