#include <iostream>
#include <stdio.h>
#include <string>
#include "SnowBross.h"
#include "Jugador.h"
#include "engine/Game.h"
#include "../common/Logger.h"
#include "../server/Server.h"
#include <socket.h>
#include <client_handler.h>
#include <signal.h>
#include "ClientData.h"
#include <Global.h>


#include <LectorJson.h>
#include <GestorEscenario.h>
#include <Data.h>
using namespace std;

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 600;

int mainServer(){

	LectorJson * lj = new LectorJson();
	cout<<"Cargando mapa tp0"<<endl;
	lj->cargarEscenario("Maps/tp0.json");
	GestorEscenario * ge = lj->obtenerGestorEscenario();
	World * w = ge->obtenerMundo();

	delete lj;

	w->start();
	cout<<"Mapa iniciado - Esperando jugadores"<<endl;

	Server * sv = new Server();
	sv->starServer(12345);


	bool commandLoop = true;
	string command;

	cout<<"Iniciado servidor en puerto 8080"<<endl;

	Data::server = sv;
	Data::world = w;


	while (commandLoop){
		cin>>command;

		if(command.compare("shutdown") == 0){
			commandLoop = false;
		}

		if(command.compare("playerlist") == 0){
			std::cout<<"Jugadores Online:"<<endl;
			for(auto p : w->getPlayerList()){
				std::cout<<p->getName()<<endl;
			}
		}

		if(command.compare("ups") == 0){
			std::cout<<"Updates por segundo "<<w->updatesPerSecond<<std::endl;
		}
	}


	std::cout<<"Cerrando server"<<endl;
	sv->stopServer();
	std::cout<<"Cerrando World;"<<endl;
	w->stop();

	w->waitWorldThread();
	std::cout<<"a borrar"<<std::endl;
	delete sv;
	delete w;
	return 0;
}

int mainCliente(){
	Logger::initializeCustomLogs();
	signal(SIGPIPE, SIG_IGN);
	Socket s = Socket(12345);

	Client_handler * c = new Client_handler(s);
	c->setDataObserver(new ClientData());

	Global::client = c;
	SnowBross *pE = new SnowBross("Snow Bross");
	Global::game = pE;
	pE->setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	pE->instantiate();

	//TODO: World ahora se tiene que venir via internet, alguien lo tiene que generar!
	//pE->setWorld(gE->obtenerMundo());
	//delete lector;

	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();

	c->stop();
	c->waitThreadEnd();

	delete c;
		//delete lector; //estamos perdiendo memoria con esto, pero falla si lo descomento..

	return 0;
}

int main(int argc, char *argv[]){
	if(argc > 1){
		return mainServer();
	}

	return mainCliente();
}
