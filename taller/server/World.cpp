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

World::World(b2Vec2 * gravity) {
	this->gravity = gravity;
	this->contactListener = new ContactListener();
	this->Box2DWorldSize = new b2Vec2(0, 0);
	this->box2DWorld = new b2World(*gravity);
	this->Box2DWorldSize = NULL;
	this->lastEntityIndex = 0;
}

b2World * World::getBox2DWorld() {
	return this->box2DWorld;
}

b2Vec2 * World::getBox2DWorldSize() {
	return this->Box2DWorldSize;
}

void World::initializePlayerBody(Jugador * player){
	b2PolygonShape box_shape;
	box_shape.SetAsBox(1, 2); //seteo los vertices del poligono

	b2FixtureDef body_fixture;
	body_fixture.shape = &box_shape;
	body_fixture.density = 1;
	body_fixture.friction = 0.2;

	b2BodyDef body_definition;
	body_definition.type = b2_dynamicBody;
	body_definition.position.Set(20, 20);

	b2Body* body = this->box2DWorld->CreateBody(&body_definition);
	b2Fixture *fixture = body->CreateFixture(&body_fixture);

	//TODO: MAX fijate que comente esto por las dudas, desp vemos
	//fixture->SetUserData((void*) 1); // Le ponemos a los poligonos el tag "1". (Para detectar colisiones)

	body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
	body->SetFixedRotation(true);

	player->setBox2DDefinitions(body, fixture);
}

Jugador * World::getPlayer(int userIndex){
	for(auto * user : this->playerList){
		if(user->getIndex() == userIndex){
			return user;
		}
	}

	return NULL;
}

void World::waitWorldThread(){
	this->worldThread.join();
}

void World::addPlayer(Jugador * jugador){
	this->playerList.push_back(jugador);
	int avavibleIndex = this->getAvavibleIndex();
	jugador->setEntityIndex(avavibleIndex);
	jugador->getClient()->userIndex = avavibleIndex;
	this->initializePlayerBody(jugador);

	for(auto * p : playerList){
		if(p->getIndex() != jugador->getIndex()){
			//Le avisamos a los demas que alguien se conecto
			this->instantiatePlayer(jugador, p->getClient());
		}

		//Te mandamos la informacion de los demas player conectados
		//incluyendote
		this->instantiatePlayer(p, jugador->getClient());
	}
}

void World::releaseEntityIndex(int index){

}

vector<Jugador *> World::getPlayerList(){
	return this->playerList;
}

void World::setUnits(int wU, int hU) {
	this->Box2DWorldSize = new b2Vec2(wU, hU);
}

void World::addPolygon(Polygon * polygon) {
	polygon->setEntityIndex(this->getAvavibleIndex());
	this->polygonList.push_back(polygon);
}

/*
b2Vec2 World::box2DToSDL(b2Vec2 * box2DCoord) {
	float sdlX = box2DCoord->x / Box2DWorldSize->x * SDLWindowSize->x;
	float sdlY = SDLWindowSize->y
			- box2DCoord->y / Box2DWorldSize->y * SDLWindowSize->y;
	b2Vec2 sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

b2Vec2 World::box2DToSDLSize(b2Vec2 * box2DCoord) {
	float sdlX = box2DCoord->x / Box2DWorldSize->x * SDLWindowSize->x;
	float sdlY = box2DCoord->y / Box2DWorldSize->y * SDLWindowSize->y;
	b2Vec2 sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

b2Vec2 World::SDLToBox2DSize(b2Vec2 * SDLCoord) {
	float b2DX = SDLCoord->x / SDLWindowSize->x * Box2DWorldSize->x;
	float b2DY = SDLCoord->y / SDLWindowSize->y * Box2DWorldSize->y;
	b2Vec2 box2DCoord(b2DX, b2DY);
	return box2DCoord;
}

b2Vec2 World::SDLToBox2D(b2Vec2 * SDLCoord) {
	float b2DX = SDLCoord->x / SDLWindowSize->x * Box2DWorldSize->x;
	float b2DY = (SDLCoord->y - SDLWindowSize->y) / SDLWindowSize->y
			* Box2DWorldSize->y;
	b2Vec2 box2DCoord(b2DX, b2DY);
	return box2DCoord;
}
*/

void World::worldStep(int delta) {
	float32 timeStep = ((float) delta) / 1000;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	this->box2DWorld->Step(timeStep, velocityIterations, positionIterations);
}

void World::instantiatePlayer(Personaje * p, Client_handler * client){
	Message m;
	m.addCommandCode(ADD_PLAYER_DATA);
	m.addChar(p->getIndex());
	m.addFloat(&p->getPosition()->x);
	m.addFloat(&p->getPosition()->y);
	m.addChar(p->getCurrentAnimation());
	m.addEndChar();

	client->send_message(&m);
}

int World::getAvavibleIndex(){
	int p = lastEntityIndex;
	lastEntityIndex ++;
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

void World::start(){
	this->wordLoop = true;
	this->worldThread = thread(World::worldLoop, this);
}

void World::stop(){
	this->wordLoop = false;
}

bool World::isOnLoop(){
	return this->wordLoop;
}

void World::worldLoop(World * word){
	int tLoop = 25;
	while(word->isOnLoop()){

		for(auto * j : word->getPlayerList()){
			j->apllyCodes();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(tLoop));
		word->worldStep(tLoop);
		word->sendUpdates();
	}
}

void World::sendUpdates(){
	for(auto * p : polygonList){
		if(!p->isStatic()){
			this->updatePolygon(p);
		}
	}

	for(auto * j : playerList){
		this->updatePeople(j);
	}
}

void World::updatePolygon(Polygon * p){
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

void World::updatePeople(Personaje * p){
	Message m;
	m.addCommandCode(UPDATE_PLAYER_ENTITY);
	m.addChar(p->getIndex());
	m.addFloat(&p->getPosition()->x);
	m.addFloat(&p->getPosition()->y);
	m.addChar(p->getCurrentAnimation());
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

void World::sendToWorldPlayers(Message * m){
	for(auto * p: this->playerList){
		if(p->getClient()->isConnected()){
			p->getClient()->send_message(m);
		}
	}
}
