#include <signal.h>
#include <iostream>
#include <string>

#include "../common/client_handler.h"
#include "../common/Logger.h"
#include "../common/socket.h"
#include "../server/Data.h"
#include "../server/Enemigo.h"
#include "../server/GestorEscenario.h"
#include "../server/Jugador.h"
#include "../server/LectorJson.h"
#include "../server/moving_objects/move_patterns/standar_movement_strategy.h"
#include "../server/Server.h"
#include "../server/World.h"
#include "ClientData.h"
#include "Global.h"
#include "SnowBross.h"

using namespace std;

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 600;

int mainServer() {

	LectorJson * lj = new LectorJson();
	cout << "Cargando mapa nivel0" << endl;
	lj->cargarEscenario("Maps/nivel0.json");
	GestorEscenario * ge = lj->obtenerGestorEscenario();
	World * w = ge->obtenerMundo();

	delete lj;

	cout << "Mapa iniciado - Esperando jugadores" << endl;

	Server * sv = new Server();
	sv->starServer(8080);

	bool commandLoop = true;
	string command;

	cout << "Iniciado servidor en puerto 8080" << endl;

	Data::server = sv;
	Data::world = w;

	while (commandLoop) {
		cin >> command;

		if (command.compare("shutdown") == 0) {
			commandLoop = false;
		}

		if (command.compare("playerlist") == 0) {
			std::cout << "Jugadores Online:" << endl;
			for (auto p : w->getPlayerList()) {
				std::cout << p->getName() << endl;
			}
		}

		if (command.compare("ups") == 0) {
			std::cout << "Updates por segundo " << w->updatesPerSecond
					<< std::endl;
		}

		if (command.compare("nextlevel") == 0) {
			Data::world->nextLevel();
		}

		if (command.compare("restartlevel") == 0) {
			Data::world->restartLevel();
		}

		if (command.compare("hit") == 0) {
			Data::world->getPlayerList()[0]->hit();
		}
	}

	std::cout << "Cerrando Server" << endl;
	sv->stopServer();
	std::cout << "Cerrando World" << endl;
	w->stop();
	w->waitWorldThread();

	delete sv;
	delete Data::world;
	return 0;
}

int mainCliente(const char * ip) {
	Logger::initializeCustomLogs();
	signal(SIGPIPE, SIG_IGN);
	Socket * s = new Socket(8080, ip);

	Client_handler * c = new Client_handler();
	c->setDataObserver(new ClientData());
	if (s == NULL)
		cout << "Socket es NULL." << endl;
	c->setSocket(s);

	Global::client = c;
	SnowBross *pE = new SnowBross("Snow Bross");
	Global::game = pE;
	pE->setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	pE->instantiate();

	c->startLoop();

	//TODO: World ahora se tiene que venir via internet, alguien lo tiene que generar!
	//pE->setWorld(gE->obtenerMundo());
	//delete lector;

	pE->setMaxFPS(50);
	pE->showFPS(true);
	pE->start();

	c->stop();
	c->waitThreadEnd();

	delete c;
	delete pE;
	//delete lector; //estamos perdiendo memoria con esto, pero falla si lo descomento..

	return 0;
}

int main(int argc, char *argv[]) {
       	if (argc > 1) {
		return mainCliente(argv[1]);
	}

	return mainServer();
}
