/*
 * World.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "World.h"
#include "Personaje.h"
#include "polygons/PolygonFactory.h"
#include "polygons/Polygon.h"
#include "Data.h"
#include "ContactContainer.h"
#include "ServerData.h"
#include "LectorJson.h"
#include "GestorEscenario.h"

World::World(b2Vec2 * gravity) {
	this->gravity = gravity;
	this->contactListener = new ContactListener();
	this->Box2DWorldSize = new b2Vec2(0, 0);
	this->box2DWorld = new b2World(*gravity);
	this->Box2DWorldSize = NULL;
	this->lastEntityIndex = 0;
	this->waitingPlayers = true;
}

bool World::isWaitingForPlayers(){
	return this->waitingPlayers;
}

b2World * World::getBox2DWorld() {
	return this->box2DWorld;
}

string * World::getWorldName() {
	return this->mapName;
}

void World::setMapData(string * mapName, int maxPlayers) {
	this->mapName = mapName;
	this->maxPlayers = maxPlayers;
}

int World::getMaxPlayers() {
	return this->maxPlayers;
}

b2Vec2 * World::getBox2DWorldSize() {
	return this->Box2DWorldSize;
}

void World::initializePlayerBody(Jugador * player) {

	double longX = 1.2f;
	double longY = 1.8f;

	b2PolygonShape box_shape;
	box_shape.SetAsBox(longX, longY); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;
	body_fixture.density = 1;
	body_fixture.friction = 0.05;
	body_fixture.filter.categoryBits = 0x0002; // Categoria para evitar que 2 jugadores colisionen.
	body_fixture.filter.groupIndex = -2;

	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;
	body_definition.position.Set(20, 20);

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);

	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
	body->SetFixedRotation(true);

	player->setBox2DDefinitions(body, fixture);

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(longX, longY);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0;

	b2Fixture *bodyFixture = body->CreateFixture(&fixtureDef);
	bodyFixture->SetUserData(
			new ContactContainer(ContactContainer::SENSORDELPIE, player));

	dynamicBox.SetAsBox(longX - 0.2, 0.4, b2Vec2(0, -longY), 0);
	fixtureDef.density = 0;
	bodyFixture->SetSensor(true);
	fixtureDef.isSensor = true;
	b2Fixture * footSensor = body->CreateFixture(&fixtureDef);
	footSensor->SetUserData(
			new ContactContainer(ContactContainer::JUGADOR, player));
	ContactListener * footListener = new ContactListener();

	player->setListenerTouchingGround(footListener);
	box2DWorld->SetContactListener(new ContactListener());

}

Jugador * World::getPlayer(int userIndex) {
	for (auto * user : this->playerList) {
		if (user->getIndex() == userIndex) {

			return user;
		}
	}
	return NULL;
}

void World::waitWorldThread() {
	this->worldThread.join();
}

void World::requestKeyData(Jugador * j) {
	Message m;
	m.addCommandCode(REQUEST_KEY_DATA);
	m.addEndChar();
	j->getClient()->send_message(&m);
}

void World::addPlayer(Jugador * jugador, bool reconecting) {
	worldMutex.lock();
	bool start = false;

	if (!reconecting) {
		this->playerList.push_back(jugador);
		int avavibleIndex = this->getAvavibleIndex();
		jugador->setEntityIndex(avavibleIndex);
		jugador->getClient()->userIndex = avavibleIndex;
		this->initializePlayerBody(jugador);

		//Si se cumple cantidad minima de jugadores arrancamos!
		if(this->playerList.size() >= this->minPlayers && waitingPlayers){
			waitingPlayers = false;
			start = true;
			this->start();
		}
	}

	Message m;
	m.addCommandCode(START_GAME);
	m.addEndChar();

	for (auto * p : playerList) {
		if (!reconecting) {
			if (p->getIndex() != jugador->getIndex()) {
				//Le avisamos a los demas que alguien se conecto
				this->instantiatePlayer(jugador, p->getClient());
			}
		}

		//Te mandamos la informacion de los demas player conectados
		//incluyendote
		this->instantiatePlayer(p, jugador->getClient());

		if(start){
			if(!p->isOffline()){
				p->getClient()->send_message(&m);
			}
		}
	}


	worldMutex.unlock();
}

void World::releaseEntityIndex(int index) {

}

vector<Jugador *> World::getPlayerList() {
	return this->playerList;
}

void World::setUnits(int wU, int hU) {
	this->Box2DWorldSize = new b2Vec2(wU, hU);
}

void World::addPolygon(Polygon * polygon) {
	polygon->setEntityIndex(this->getAvavibleIndex());
	this->polygonList.push_back(polygon);
}

void World::worldStep(int delta) {
	float32 timeStep = ((float) delta) / 1000;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	this->box2DWorld->Step(timeStep, velocityIterations, positionIterations);
}

void World::instantiatePlayer(Jugador * p, Client_handler * client) {
	Message m;
	m.addCommandCode(ADD_PLAYER_DATA);
	m.addChar(p->getIndex());
	m.addFloat(&p->getPosition()->x);
	m.addFloat(&p->getPosition()->y);
	m.addAnimationCode(p->getCurrentAnimation());
	m.addCharArray(p->getName(), strlen(p->getName()));
	m.addEndChar();

	client->send_message(&m);
}

int World::getAvavibleIndex() {
	int p = lastEntityIndex;
	lastEntityIndex++;
	return p;
}

bool World::isMainCharacterTouchingGround() {
	return contactListener->getNumberOfContacts() > 0;
}

bool World::isOutOfWorld(b2Vec2 position) {
	return ((position.x <= (-2 * this->Box2DWorldSize->x))
			|| (position.y <= (-2 * this->Box2DWorldSize->y))
			|| (position.x >= (2 * this->Box2DWorldSize->x))
			|| (position.y >= (2 * this->Box2DWorldSize->y)));
}

vector<Polygon *> World::getPolygonList() {
	return this->polygonList;
}

void World::start() {
	this->wordLoop = true;
	this->worldThread = thread(World::worldLoop, this);
}

void World::stop() {
	this->wordLoop = false;
}

bool World::isOnLoop() {
	return this->wordLoop;
}

void World::setMinPlayers(int minPlayers){
	this->minPlayers = minPlayers;
}

void World::nextLevel(World* currentLevel) {
	Message m;
	m.addCommandCode(END_LEVEL);
	m.addEndChar();
	currentLevel->sendToWorldPlayers(&m);

	//Lo unico que se transfiere de nivel a nivel es la lista de jugadores!
	vector<Jugador *> pList = currentLevel->getPlayerList();

	currentLevel->stop();
	currentLevel->waitWorldThread();
	delete currentLevel;

	LectorJson * lj = new LectorJson();
	lj->cargarEscenario("Maps/tp0.json");
	GestorEscenario * ge = lj->obtenerGestorEscenario();
	World * w = ge->obtenerMundo();

	Data::world = w;

	for(auto * player : pList){
		//w->logginUser(player->getName(), player->getClient());
		delete player;
	}

	pList.clear();

	delete lj;
}

void World::logginUser(string userName, Client_handler* client) {

		Message envio;
	// Comparacion para ver si ya existe el nombre en uso.
		bool reconecting = false;
		Jugador * reconectedPlayer = NULL;

		for (auto * p : this->playerList) {
			string oPlayer(p->getName());

			if (oPlayer.compare(userName) == 0) {

				if (p->isOffline()) {
					reconecting = true;
					reconectedPlayer = p;
					break;
				} else {
					envio.addCommandCode(ERROR_MESSAGE);
					envio.addCharArray("Jugador Online\0", 15);
					envio.addCharArray(
							"El nombre que intenta utilizar se encuentra en uso\0",
							51);
					envio.addEndChar();
					client->send_message(&envio);
					return;
				}
			}
		}

		// Ver si ya esta lleno.
		if (!reconecting) {
			if (this->getPlayerList().size()
					>= this->getMaxPlayers()) {
				envio.addCommandCode(ERROR_MESSAGE);
				envio.addCharArray("Lugares\0", 8);
				envio.addCharArray("No hay mas lugar\0", 17);
				envio.addEndChar();
				client->send_message(&envio);
				return;
			}
		}

		//Mandamos un mensaje por poligono!
		envio.addCommandCode(INITIALIZE_MAP);
		envio.addFloat(&this->getBox2DWorldSize()->x);
		envio.addFloat(&this->getBox2DWorldSize()->y);
		envio.addChar(this->isWaitingForPlayers());
		envio.addEndChar();
		client->send_message(&envio);

		vector<Polygon*> polList = this->getPolygonList();

		for (auto * p : polList) {
			Message * mapData = new Message();
			mapData->addCommandCode(ADD_MAP_DATA);

			char vNum = p->getPointList().size();
			mapData->addChar(p->getEntityIndex());
			mapData->addChar(p->isStatic());
			mapData->addChar(p->getType());
			mapData->addChar(vNum);
			mapData->addFloat(&p->getPosition()->x);
			mapData->addFloat(&p->getPosition()->y);
			float rotation = p->getRotation();
			mapData->addFloat(&rotation);

			for (auto * ver : p->getPointList()) {
				mapData->addFloat(&ver->x);
				mapData->addFloat(&ver->y);
			}

			mapData->addEndChar();
			client->send_message(mapData);

			delete mapData;
		}

		Jugador * j;

		if (!reconecting) {
			Message m;
			m.addCommandCode(SHOW_MESSAGE);
			string pM("");
			pM.append(userName);
			pM.append(" se ha conectado");
			m.addCharArray(pM.c_str(), pM.size());
			m.addEndChar();
			this->sendToWorldPlayers(&m);

			j = new Jugador(client, (char *)userName.c_str());
			j->setOffline(false); //FIXME: agregue esto porque sino queda sin inicializar. No se si va en false..

		} else {
			Message m;
			m.addCommandCode(SHOW_MESSAGE);
			string pM("");
			pM.append(reconectedPlayer->getName());
			pM.append(" se ha reconectado");
			m.addCharArray(pM.c_str(), pM.size());
			m.addEndChar();

			this->sendToWorldPlayers(&m);
			client->userIndex = reconectedPlayer->getIndex();
			reconectedPlayer->setClient(client);
			j = reconectedPlayer;
			j->setOffline(false);
		}

		this->addPlayer(j, reconecting);

		Message * mainEntity = new Message();
		mainEntity->addCommandCode(LOCK_CAMERA_ENTITY);
		char mEntity = j->getIndex();
		mainEntity->addChar(mEntity);
		mainEntity->addEndChar();
		client->send_message(mainEntity);
		delete mainEntity;

		Message * finalData = new Message();
		finalData->addCommandCode(INITIALIZE_GRAPHICS);
		finalData->addChar(j->getPlayerLives());
		finalData->addChar(j->getPlayerScore());
		finalData->addEndChar();
		client->send_message(finalData);
		delete finalData;

		return;
}

void World::worldLoop(World * world) {
	char eCode = 0;
	try {
		int ups = 30;
		int sleepTime = 1000 / ups;

		unsigned int updateCount = 0;

		while (world->isOnLoop()) {
			eCode = 0;

			for (auto * j : world->getPlayerList()) {
				j->apllyCodes();
				j->update();
			}

			eCode = 3;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

			//worldMutex.lock();
			eCode = 4;
			for (auto * j : world->getPlayerList()) {
				if (!j->isOffline()) {
					world->requestKeyData(j);
				}
			}
			//worldMutex.unlock();

			eCode = 5;
			world->worldStep(sleepTime);
			eCode = 6;

			if ((updateCount % 2) == 0) {
				world->sendUpdates();
			}
			updateCount++;

			for (auto * j : world->getPlayerList()) {
				if (!j->isOffline()) {
					if (j->keyRequestSend >= 60) {
						j->setOffline(true);
						Message m;
						m.addCommandCode(SHOW_MESSAGE);
						string pM("");
						pM.append(j->getName());
						pM.append(" se ha desconectado");
						m.addCharArray(pM.c_str(), pM.size());
						m.addEndChar();

						Data::world->sendToWorldPlayers(&m);

					}
				}
			}
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << " - Producido en WorldLoop - tCode: " << eCode
				<< std::endl;
		exit(-1);
	}
}

void World::sendUpdates() {
	for (auto * j : playerList) {
		//this->updateTiming(j);
		this->updatePeople(j);
		if (!j->isOffline()) {
			j->keyRequestSend++;
		}
	}

	for (auto * p : polygonList) {
		if (!p->isStatic()) {
			this->updatePolygon(p);
		}
	}
}

void World::updateTiming(Jugador * j) {
	Message m;
	m.addCommandCode(UPDATE_TIMING);
	char timing = 1000 / (this->updatesPerSecond + 1);
	m.addChar(timing);
	m.addEndChar();

	j->getClient()->send_message(&m);
}

void World::updatePolygon(Polygon * p) {
	Message m;
	m.addCommandCode(UPDATE_ENTITY);
	m.addChar(p->getEntityIndex());
	m.addFloat(&p->getPosition()->x);
	m.addFloat(&p->getPosition()->y);
	float rotation = p->getRotation();
	m.addFloat(&rotation);

	m.addEndChar();

	this->sendToWorldPlayers(&m);
}

void World::updatePeople(Jugador * p) {
	Message m;
	m.addCommandCode(UPDATE_PLAYER_ENTITY);
	m.addChar(p->getIndex());
	m.addFloat(&p->getPosition()->x);
	m.addFloat(&p->getPosition()->y);
	m.addAnimationCode(p->getCurrentAnimation());
	m.addChar(p->isOffline());
	m.addEndChar();

	this->sendToWorldPlayers(&m);
}

World::~World() {
	delete this->contactListener;

	delete this->gravity;
	delete this->box2DWorld;

	for (auto *polygon : polygonList) {
		delete polygon;
	}

	polygonList.clear();
}

void World::sendToWorldPlayers(Message * m) {
	for (auto * p : this->playerList) {
		if (!p->isOffline()) {
			p->getClient()->send_message(m);
		}
	}
}

