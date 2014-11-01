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
#include <CommandCode.h>
#include <Message.h>

using namespace std;

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 600;

int mainServer(){
	Server * sv = new Server();
	sv->starServer(8080);


	bool commandLoop = true;
	string command;

	cout<<"Iniciado servidor en puerto 8080"<<endl;
	while (commandLoop){
		cin>>command;

		if(command.compare("shutdown") == 0){
			commandLoop = false;
		}
	}

	sv->stopServer();
	return 0;
}

int mainCliente(){
	Logger::initializeCustomLogs();
	signal(SIGPIPE, SIG_IGN);
	Socket s = Socket(8080);

	Client_handler * c = new Client_handler(s);
	c->setDataObserver(new ClientData());

	Message * m = new Message();
	m->addCommandCode(IM_LOGGED);
	c->send_message(m);
	delete m;

	SnowBross *pE = new SnowBross("Snow Bross");
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
