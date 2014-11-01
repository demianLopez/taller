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

World::World(b2Vec2 * gravity) {
	this->gravity = gravity;
	this->contactListener = new ContactListener();
	this->Box2DWorldSize = new b2Vec2(0, 0);
	this->box2DWorld = new b2World(*gravity);
	this->Box2DWorldSize = NULL;
}

b2World * World::getBox2DWorld() {
	return this->box2DWorld;
}

b2Vec2 * World::getBox2DWorldSize() {
	return this->Box2DWorldSize;
}

void World::waitWorldThread(){
	this->worldThread.join();
}

void World::addPlayer(Jugador * jugador){
	this->playerList.push_back(jugador);
}

vector<Jugador *> World::getPlayerList(){
	return this->playerList;
}

void World::setUnits(int wU, int hU) {
	this->Box2DWorldSize = new b2Vec2(wU, hU);
}

void World::addPolygon(Polygon * polygon) {
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
	while(word->isOnLoop()){
		//Word logic!

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
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

