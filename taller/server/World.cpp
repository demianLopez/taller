/*
 * World.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "World.h"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Common/b2Settings.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <cstring>
#include <string>

#include "../common/client_handler.h"
#include "../common/CommandCode.h"
#include "../common/Message.h"
#include "ContactContainer.h"
#include "ContactListener.h"
#include "Data.h"
#include "GestorEscenario.h"
#include "LectorJson.h"

World::World(b2Vec2* gravity) {
	this->gravity = gravity;
	this->contactListener = new ContactListener();
	this->Box2DWorldSize = new b2Vec2(0, 0);
	this->box2DWorld = new b2World(*gravity);
	this->Box2DWorldSize = NULL;
	this->lastEntityIndex = 0;
	this->waitingPlayers = true;
	this->isRestarting = false;
	this->wordLoop =false;
	this->changin = false;

	for(int i = 0; i < 40; i++){
		Disparo * p = new Disparo(this->getAvavibleIndex());
		this->projectileList.push_back(p);
		this->initializeProjectile(p, 0);
	}

	for(int i = 0; i < 6; i ++){
		Item * it = new Item(this->getAvavibleIndex());
		this->bonusList.push_back(it);
		this->initializeBonus(it);
	}

	for(int i = 0; i < 4; i++){
		Disparo * p = new Disparo(this->getAvavibleIndex());
		this->projectileList.push_back(p);
		this->initializeProjectile(p, 1);
		this->enemyProjectile.push_back(p);
	}

	box2DWorld->SetContactListener(new ContactListener());


	this->myWater = NULL;
}

Jugador * World::getFirstAlive(){
	for(auto * p : playerList){
		if(!p->isDead()){
			return p;
		}
	}

	return NULL;
}


bool World::isWaitingForPlayers(){
	return this->waitingPlayers;
}

void World::instantiateWater(float posX, float posY, float height, float width){
	b2PolygonShape box_shape;
	box_shape.SetAsBox(height, width); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;

	body_fixture.filter.categoryBits = 0x0008;
	body_fixture.filter.maskBits = 0x0001 | 0x0002 | 0x0004 | 0x0020;
	body_fixture.isSensor = true;


	b2BodyDef body_definition;
	body_definition.type = b2_staticBody;
	body_definition.position.Set(posX, posY);

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);

	fixture->SetUserData(
				new ContactContainer(ContactContainer::AGUA, NULL));
	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
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

void World::evaluateBonusCreation(float posX, float posY){

	Item * usableItem = NULL;
	int type = rand() % 4 ;
	for(auto * i : bonusList){
		if(!i->isOnMap()){
			usableItem = i;
			break;
		}
	}

	if(usableItem == NULL){
		return;
	}

	usableItem->putAt(posX, posY, type);

}

void World::sendWorldInfo(Client_handler * client){
	//Mandamos un mensaje por poligono!
	Message envio = Message();

	envio.addCommandCode(INITIALIZE_MAP);
	envio.addFloat(&Data::world->getBox2DWorldSize()->x);
	envio.addFloat(&Data::world->getBox2DWorldSize()->y);
	envio.addChar(Data::world->isWaitingForPlayers());
	envio.addEndChar();
	client->send_message(&envio);

	vector<Polygon*> polList = Data::world->getPolygonList();
	for (auto * p : polList) {
		Message mapData;
		mapData.addCommandCode(ADD_MAP_DATA);
		char vNum = p->getPointList().size();
		mapData.addChar(p->getEntityIndex());
		mapData.addChar(p->isStatic());
		mapData.addChar(p->getType());
		mapData.addChar(vNum);
		mapData.addFloat(&p->getPosition()->x);
		mapData.addFloat(&p->getPosition()->y);
		float rotation = p->getRotation();
		mapData.addFloat(&rotation);
		for (auto * ver : p->getPointList()) {
			mapData.addFloat(&ver->x);
			mapData.addFloat(&ver->y);
		}
		mapData.addEndChar();
		client->send_message(&mapData);
	}

	for(auto * e : enemyList){
		this->instantiateEnemy(e, client);
	}

	Message p;
	p.addCommandCode(INSTANTIATE_PROJECTILES);
	p.addChar(projectileList[0]->getIndex());
	p.addChar(projectileList[projectileList.size() - 1]->getIndex());
	p.addChar(0);
	p.addEndChar();

	client->send_message(&p);

	Message b;
	b.addCommandCode(INSTANTIATE_BONUS);
	b.addChar(bonusList[0]->getIndex());
	b.addChar(bonusList[bonusList.size() - 1]->getIndex());
	b.addEndChar();

	client->send_message(&b);

	Message pe;
	pe.addCommandCode(INSTANTIATE_PROJECTILES);
	pe.addChar(enemyProjectile[0]->getIndex());
	pe.addChar(enemyProjectile[enemyProjectile.size() - 1]->getIndex());
	pe.addChar(1);
	pe.addEndChar();
	client->send_message(&pe);
	
	if(this->myWater){
		Message waterMessage;
		waterMessage.addCommandCode(ADD_WATER);
		waterMessage.addChar(myWater->getIndex());
		float w = myWater->getSize().x * 2;
		float h = myWater->getSize().y * 2;
		float x = myWater->getPosition().x;
		float y = myWater->getPosition().y;
		waterMessage.addFloat(&x);
		waterMessage.addFloat(&y);
		waterMessage.addFloat(&w);
		waterMessage.addFloat(&h);
		waterMessage.addEndChar();

		client->send_message(&waterMessage);
	}
}

void World::initializeEnemyBody(Enemigo * enemy){
	double longX = 1.2f;
	double longY = 1.8f;

	b2PolygonShape box_shape;
	box_shape.SetAsBox(longX, longY); //seteo los vertices del poligono

	b2CircleShape circle_shape;
	float32 radius = 1.0;
	circle_shape.m_radius = radius;

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;
	body_fixture.density = 1;
	body_fixture.friction = 0.05;

	body_fixture.filter.categoryBits = 0x0004;// Categoria para evitar que 2 jugadores colisionen.
	body_fixture.filter.maskBits = 0x0008 | 0x0001 | 0x0020 | 0x0040;
	//body_fixture.filter.groupIndex = -3;


	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;
	body_definition.position.Set(enemy->getx(),enemy->gety());

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);
	//fixture->SetSensor(true);

	fixture->SetUserData(
				new ContactContainer(ContactContainer::ENEMY, enemy));
	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
	body->SetFixedRotation(true);

	enemy->setBox2DDefinitions(body, fixture);

	box_shape.SetAsBox(longX - 0.2, 0.4, b2Vec2(0, -longY), 0);
	body_fixture.density = 0;

	body_fixture.isSensor = true;
	b2Fixture * footSensor = body->CreateFixture(&body_fixture);
	footSensor->SetUserData(
			new ContactContainer(ContactContainer::SENSORDELPIE, enemy));
	ContactListener * footListener = new ContactListener();

	enemy->setListenerTouchingGround(footListener);

	box_shape.SetAsBox(longX - 0.2, 0.8, b2Vec2(0, longY), 0);
	body_fixture.shape = &box_shape;
	body_fixture.density = 0;

	body_fixture.isSensor = true;
	b2Fixture * headSensor = body->CreateFixture(&body_fixture);
	headSensor->SetUserData(
			new ContactContainer(ContactContainer::SENSORDELACABEZA, enemy));
	ContactListener * headListener = new ContactListener();

	enemy->setHeadListener(headListener);
}

void World::initializeEnemySnowBall(Enemigo * enemy){

	b2CircleShape circle_shape;
	float32 radius = 1.9;
	circle_shape.m_radius = radius;

	b2FixtureDef body_fixture;
	body_fixture.shape = &circle_shape;
	body_fixture.density = 0.1;
	body_fixture.restitution = 1.0;

	body_fixture.filter.categoryBits = 0x0002;
	body_fixture.filter.maskBits = 0x0008;


	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;
	body_definition.position.Set(enemy->getx(),enemy->gety());

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);

	b2FixtureDef body_fixture2;
	body_fixture2.shape = &circle_shape;
	body_fixture2.isSensor = true;
	body_fixture2.filter.categoryBits = 0x00040;
	body_fixture2.filter.maskBits = 0x0001 | 0x0004;

	fixture->SetUserData(
				new ContactContainer(ContactContainer::SNOW_BALL_ENEMY, enemy));

	fixture = body->CreateFixture(&body_fixture2);
	fixture->SetUserData(
					new ContactContainer(ContactContainer::SNOW_BALL_ENEMY, enemy));
	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
	//fixture->SetSensor(true);
	enemy->setBox2DDefinitions(body, fixture);
}


void World::initializeBonus(Item * item){
	double longX = 0.6f;
	double longY = 0.6f;

	b2PolygonShape box_shape;
	box_shape.SetAsBox(longX, longY); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;

	body_fixture.filter.categoryBits = 0x0010;
	body_fixture.filter.maskBits = 0x0001;
	body_fixture.isSensor = true;


	b2BodyDef body_definition;
	body_definition.type = b2_staticBody;
	body_definition.position.Set(0, 0);

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);

	fixture->SetUserData(
				new ContactContainer(ContactContainer::BONUS, item));
	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
	body->SetActive(false);

	item->setBox2DDefinitions(body, fixture);

}

void World::initializeProjectile(Disparo * projectile, int type){
	b2CircleShape circle_shape;

	float32 radius = 0.15;
	circle_shape.m_radius = radius;

	b2FixtureDef body_fixture;
	body_fixture.shape = &circle_shape;
	body_fixture.density = 1;
	body_fixture.friction = 0.5;
	body_fixture.isSensor = true;
	body_fixture.filter.categoryBits = 0x0020;
	body_fixture.filter.maskBits = 0x0001 | 0x0004 | 0x0008;

	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;

	body_definition.position.Set(0, 0); //seteo posicion base

	b2Body * body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);

	if(type == 1){
		body->SetGravityScale(0);
	}

	if(type == 0){
		fixture->SetUserData(new ContactContainer(ContactContainer::DISPARO_JUGADOR, projectile)); // Para detectar colisiones.
	} else {
		fixture->SetUserData(new ContactContainer(ContactContainer::DISPARO_ENEMIGO, projectile)); // Para detectar colisiones.
	}
	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas

	projectile->setBox2DDefinitions(body, fixture);
	body->SetActive(false);
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

	body_fixture.filter.categoryBits = 0x0001; // Categoria para evitar que 2 jugadores colisionen.
	body_fixture.filter.maskBits = 0x0008 | 0x0004 | 0x0010 | 0x0020 | 0x0040;
	//body_fixture.filter.groupIndex = -2;

	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;

	int indx = player->getIndex() % 4;
	body_definition.position.Set(this->playerPos[indx]->x, this->playerPos[indx]->y);

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);
	fixture->SetUserData(
			new ContactContainer(ContactContainer::JUGADOR, player));

	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
	body->SetFixedRotation(true);

	player->setBox2DDefinitions(body, fixture);

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(longX - 0.2, 0.4, b2Vec2(0, -longY), 0);
	body_fixture.shape = &dynamicBox;
	body_fixture.density = 0;

	body_fixture.isSensor = true;
	b2Fixture * footSensor = body->CreateFixture(&body_fixture);
	footSensor->SetUserData(
			new ContactContainer(ContactContainer::SENSORDELPIE, player));
	ContactListener * footListener = new ContactListener();

	player->setListenerTouchingGround(footListener);

	dynamicBox.SetAsBox(longX - 0.2, 0.8, b2Vec2(0, longY), 0);
	body_fixture.shape = &dynamicBox;
	body_fixture.density = 0;

	body_fixture.isSensor = true;
	b2Fixture * headSensor = body->CreateFixture(&body_fixture);
	headSensor->SetUserData(
			new ContactContainer(ContactContainer::SENSORDELACABEZA, player));
	ContactListener * headListener = new ContactListener();

	player->setHeadListener(headListener);
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
	if(this->worldThread.joinable()){
		this->worldThread.join();
	}
}

void World::requestKeyData(Jugador * j) {
	Message m;
	m.addCommandCode(REQUEST_KEY_DATA);
	m.addEndChar();
	j->getClient()->send_message(&m);
}

void World::checkPlayerCount(){
	if(this->playerList.size() >= this->minPlayers && this->waitingPlayers){
		waitingPlayers = false;

		Message m;
		m.addCommandCode(START_GAME);
		m.addEndChar();

		for(auto * p: playerList){
			if(!p->isOffline()){
				p->getClient()->send_message(&m);
			}
		}

		this->start();
	}
}

void World::addEnemy(Enemigo * enemy){

	this->enemyList.push_back(enemy);
	int avavibleIndex = this->getAvavibleIndex();
	enemy->setEntityIndex(avavibleIndex);
	this->initializeEnemyBody(enemy);

	for (auto * p : playerList) {
		if(!p->isOffline()){
			this->instantiateEnemy(enemy, p->getClient());
		}
	}
}

void World::addPlayer(Jugador * jugador, bool reconecting) {
	worldMutex.lock();

	if (!reconecting) {
		this->playerList.push_back(jugador);
		int avavibleIndex = this->getAvavibleIndex();
		jugador->setEntityIndex(avavibleIndex);
		jugador->getClient()->userIndex = avavibleIndex;
		this->initializePlayerBody(jugador);
	}



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

void World::instantiateEnemy(Enemigo * e, Client_handler * client){
	Message m;
	m.addCommandCode(ADD_ENEMY_DATA);
	m.addChar(e->getIndex());
	m.addChar(e->getType());
	m.addFloat(&e->getPosition()->x);
	m.addFloat(&e->getPosition()->y);
	m.addAnimationCode(e->getCurrentAnimation());
	m.addEndChar();

	client->send_message(&m);
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

Water* World::getWater(){
	return this->myWater;
}

void World::setWater(){
	float pX = 15.0;
	float pY = 8.5;
	float w = 16.0;
	float h = 8.0;
	myWater = new Water(99);
	myWater->setPosition(pX, pY, w, h);
	this->instantiateWater(pX, pY, w, h);
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

void World::nextSecond() {
	for(auto * p : this->playerList){
		p->checkStatus();
	}

	for(auto * p : this->projectileList){
		p->checkStatus();
	}

	for(auto * p : this->enemyProjectile){
		p->checkStatus();
	}

	for(auto * e : this->enemyList){
		e->checkStatus();
	}
}

vector<Enemigo*> World::getEnemyList() {
	return this->enemyList;
}

void World::addPlayerPos(float x, float y){
	this->playerPos.push_back(new b2Vec2(x, y));
}

void World::enemyShooting(Enemigo * e){

	Disparo * pLibre = NULL;

	for(auto * p : enemyProjectile){
		if(!p->isOnUse()){
			pLibre = p;
			break;
		}
	}

	if(pLibre == NULL){
		return;
	}

	float pX = e->getPosition()->x;
	float pY = e->getPosition()->y;

	pLibre->enemyShoot(pX, pY, e);

	Message m;
	m.addCommandCode(SHOOT_PROJECTILE);
	m.addChar(pLibre->getIndex());
	m.addFloat(&pX);
	m.addFloat(&pY);
	m.addEndChar();

	this->sendToWorldPlayers(&m);
}

void World::playerShooting(Jugador* j) {

	Disparo * pLibre = NULL;

	for(auto * p : projectileList){
		if(!p->isOnUse()){
			pLibre = p;
			break;
		}
	}

	if(pLibre == NULL){
		return;
	}

	float pX = j->getPosition()->x;
	float pY = j->getPosition()->y;

	pLibre->shoot(pX, pY, j);

	Message m;
	m.addCommandCode(SHOOT_PROJECTILE);
	m.addChar(pLibre->getIndex());
	m.addFloat(&pX);
	m.addFloat(&pY);
	m.addEndChar();

	this->sendToWorldPlayers(&m);
}

void World::addAfterChange(B2DAfterChange* ac) {
	this->afterChangeList.push_back(ac);
}

void World::realizeAfterChange() {
	for(auto * ac: afterChangeList){
		ac->change();
	}

	afterChangeList.clear();
}

b2Vec2* World::getPlayerInitialPos(int index) {
	return this->playerPos[index % 4];
}

void World::changeLevel(World * currentLevel, char * nextLevel, bool wonLevel) {
	currentLevel->changin = true;
	currentLevel->stop();
	currentLevel->waitWorldThread();
	//Lo unico que se transfiere de nivel a nivel es la lista de jugadores!
	vector<Jugador *> pList = currentLevel->getPlayerList();

	for(auto * pm : pList){
		Message m;
		m.addCommandCode(END_LEVEL);
		m.addChar(pList.size());
		for(auto * p : pList){
			string n(p->getName());
			m.addCharArray(n.c_str(), n.size());
			m.addChar(p->getPlayerScore());
			m.addChar(!p->isOffline());
			m.addChar(p->isDead());
		}

		m.addChar(wonLevel);
		m.addChar(pm->isDead());
		m.addEndChar();

		if(!pm->isOffline()){
			pm->getClient()->send_message(&m);
		}
	}


	//Esperamos que todos se pongan en READY!
	bool notReady = true;

	while(notReady){
		bool someoneNotReady = true;
		for(auto * p : pList){
			p->playerBusy.lock();
			someoneNotReady = someoneNotReady && (p->isReady || p->isOffline() || (p->isDead() && wonLevel));
			p->playerBusy.unlock();
		}

		notReady = !someoneNotReady;
	}

	LectorJson * lj = new LectorJson();
	lj->cargarEscenario(nextLevel);
	GestorEscenario * ge = lj->obtenerGestorEscenario();
	World * w = ge->obtenerMundo();

	delete currentLevel;

	Data::world = w;
	for(auto * player : pList){
		if(wonLevel || !player->isOffline()){
			if(!player->isOffline()){
				w->sendWorldInfo(player->getClient());
			}

			Jugador * nJugador = player->clonePlayer(wonLevel);
			w->addPlayer(nJugador, false);

			if(!player->isOffline()){
				Message * mainEntity = new Message();
				mainEntity->addCommandCode(LOCK_CAMERA_ENTITY);
				char mEntity = nJugador->getIndex();
				mainEntity->addChar(mEntity);
				mainEntity->addEndChar();
				nJugador->getClient()->send_message(mainEntity);
				delete mainEntity;

				Message * finalData = new Message();
				finalData->addCommandCode(INITIALIZE_GRAPHICS);
				finalData->addChar(nJugador->getPlayerLives());
				finalData->addChar(nJugador->getPlayerScore());
				finalData->addEndChar();
				nJugador->getClient()->send_message(finalData);


				delete finalData;
			}

		}
		delete player;
	}
	pList.clear();

	w->checkPlayerCount();
	delete lj;
}

void World::nextLevel(){
	new thread(World::changeLevel, this, (char *)this->nextLevelName.c_str(), true);
}

void World::restartLevel(){
	new thread(World::changeLevel, this, (char *)"Maps/nivel0.json", false);
}

void World::setCurrentLevelName(char* currentLevelName) {
	this->currentLevelName = string(currentLevelName);
}

void World::setNextLevelName(char* nextLevelName) {
	this->nextLevelName = string(nextLevelName);
}

void World::worldLoop(World * world) {

	int ups = 30;
	int sleepTime = 1000 / ups;

	unsigned int updateCount = 0;

	unsigned int elapsedTime = 0;

	for(auto * p: world->getPlayerList()){
		if(p->isDead()){
			p->deadEvent(false);
		}
	}

	while (world->isOnLoop()) {

		for (auto * j : world->getPlayerList()) {
			j->apllyCodes();
			j->update();
		}

		if(world->getPlayerList().size() > 0){
			for(auto * e : world->getEnemyList()){
				//e->evaluateMovement(world->getPlayerList()[0]);
				e->movimientoLoco();
				e->update();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		elapsedTime += sleepTime;

		if(elapsedTime >= 1000){
			world->nextSecond();
			elapsedTime -= 1000;
		}


		for (auto * j : world->getPlayerList()) {
			if (!j->isOffline()) {
				world->requestKeyData(j);
			}
		}

		world->worldStep(sleepTime);
		world->realizeAfterChange();


		if ((updateCount % 1) == 0) {
			world->sendUpdates();
		}
		updateCount++;

		world->verifyLevelEndConditions();

		/*
		TODO: Esto era para verificar que nadie se desconecte con calbe, pero produce un pequeño delay
		//si en esta entrega no evaluan eso, lo dejamos asi!
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
		*/
	}
}

void World::sendUpdates() {
	for (auto * j : playerList) {
		//this->updateTiming(j);
		this->updatePeople(j);
		/*if (!j->isOffline()) {
			j->keyRequestSend++;
		}*/
	}

	for (auto * p : polygonList) {
		if (!p->isStatic()) {
			this->updatePolygon(p);
		}
	}

	for(auto * e : enemyList){
		this->updateEnemy(e);
	}

	for(auto * p : projectileList){
		if(p->isOnUse()){
			this->updateProjectile(p);
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

void World::updateProjectile(Disparo * p){
	Message m;
	m.addCommandCode(UPDATE_ENTITY);
	m.addChar(p->getIndex());
	m.addFloat(&p->getPosition()->x);
	m.addFloat(&p->getPosition()->y);
	float rotation = p->getRotation();
	m.addFloat(&rotation);

	m.addEndChar();

	this->sendToWorldPlayers(&m);
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
	m.addChar(p->isInvulnerable());
	m.addEndChar();

	this->sendToWorldPlayers(&m);
}

void World::updateEnemy(Enemigo * e){
	Message m;
	m.addCommandCode(UPDATE_ENEMY_ENTITY);
	m.addChar(e->getIndex());
	m.addFloat(&e->getPosition()->x);
	m.addFloat(&e->getPosition()->y);
	float rotation = e->getRotation();
	m.addFloat(&rotation);
	m.addAnimationCode(e->getCurrentAnimation());
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

	for(auto * d : projectileList){
		delete d;
	}

	projectileList.clear();
	polygonList.clear();
}

void World::sendToWorldPlayers(Message * m) {
	for (auto * p : this->playerList) {
		if (!p->isOffline()) {
			p->getClient()->send_message(m);
		}
	}
}

void World::add_projectile(Projectile* p) {
}

void World::verifyLevelEndConditions(){

	bool someoneEnemyAlive = false;
	if (this->isRestarting){
		return;
	}

	for(auto * e : this->enemyList){
		someoneEnemyAlive = someoneEnemyAlive || !e->isDead();
	}

	if(!someoneEnemyAlive){
		this->isRestarting = true;
		this->nextLevel();
		return;
	}


	bool someoneAlive = false;
	bool someoneConnected = false;
	for(auto * p : this->playerList){
		someoneAlive = someoneAlive || (!p->isDead() && !p->isOffline());
		someoneConnected = someoneConnected || !p->isOffline();
	}

	if(!someoneAlive && someoneConnected){
		this->isRestarting = true;
		this->restartLevel();
	}
}

