/*
 * World.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "World.h"
#include "Resources.h"
#include "Personaje.h"
#include "polygons/PolygonFactory.h"
#include "polygons/Polygon.h"

World::World(b2Vec2 * gravity) {
	this->gravity = gravity;
	this->contactListener = new ContactListener();
	this->worldResources = new Resources();
	this->mainCharacter = NULL;
	this->Box2DWorldSize = new b2Vec2(0, 0);
	this->SDLWindowSize = new b2Vec2(0, 0);
	this->box2DWorld = new b2World(*gravity);
	this->Box2DWorldSize = NULL;
	this->mainCharacter = NULL;
}

b2World * World::getBox2DWorld(){
	return this->box2DWorld;
}

void World::setUnits(int wU, int hU, int wP, int hP){
	this->Box2DWorldSize = new b2Vec2(wU, hU);
	this->SDLWindowSize = new b2Vec2(wP, hP);
}

void World::loadResources(){
	this->worldResources->loadBackground("Resources/font1.png");
	this->worldResources->loadAnimations();
}


void World::addPolygon(Polygon * polygon){
	this->polygonList.push_back(polygon);
}

b2Vec2 World::box2DToSDL(b2Vec2 * box2DCoord){
	float sdlX = box2DCoord->x/Box2DWorldSize->x * SDLWindowSize->x;
	float sdlY = SDLWindowSize->y - box2DCoord->y/Box2DWorldSize->y * SDLWindowSize->y;
	b2Vec2 sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

b2Vec2 World::box2DToSDLSize(b2Vec2 * box2DCoord){
	float sdlX = box2DCoord->x/Box2DWorldSize->x * SDLWindowSize->x;
	float sdlY = box2DCoord->y/Box2DWorldSize->y * SDLWindowSize->y;
	b2Vec2 sdlCoord(sdlX, sdlY);
	return sdlCoord;
}

b2Vec2 World::SDLToBox2D(b2Vec2 * SDLCoord){
	float b2DX = SDLCoord->x/SDLWindowSize->x * Box2DWorldSize->x;
	float b2DY = (SDLCoord->y - SDLWindowSize->y)/SDLWindowSize->y * Box2DWorldSize->y;
	b2Vec2 box2DCoord(b2DX, b2DY);
	return box2DCoord;
}

void World::worldStep(int delta){
	float32 timeStep = ((float) delta) / 1000;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	this->box2DWorld->Step(timeStep, velocityIterations, positionIterations);
}

Jugador * World::getMainCharacter(){
	return this->mainCharacter;
}

int World::getNumberOfMainCharacterContacts(){
	return contactListener->getNumberOfContacts();
}

void World::setMainCharacter(Jugador * mainCharacter){
	this->mainCharacter = mainCharacter;
	box2DWorld->SetContactListener(contactListener);
}

/*
void World::generateWorld(){
	//GENERAR BOX2D




	//WORLD!
	/*

	Polygon * piso = PolygonFactory::get_static_rectangle(25, 1, 13, 1, 0.1f, this);
	piso->setColor(200, 20, 40);
	this->addPolygon(piso);

	Polygon * paredIzquierda = PolygonFactory::get_static_rectangle(1, 19, 1, 10, 0.1f, this);
	paredIzquierda->setColor(200, 20, 40);
	this->addPolygon(paredIzquierda);

	Polygon * paredDerecha = PolygonFactory::get_static_rectangle(1, 19, 25, 10, 0.1f, this);
	paredDerecha->setColor(200, 20, 40);
	this->addPolygon(paredDerecha);

	Polygon * primerPlataforma = PolygonFactory::get_static_rectangle(5, 1, 23, 4, 0.1f, this);
	primerPlataforma->setColor(20, 200, 40);
	this->addPolygon(primerPlataforma);

	Polygon * segundaPlataforma = PolygonFactory::get_static_rectangle(5, 1, 15, 7, 0.1f, this);
	segundaPlataforma->setColor(20, 40, 200);
	this->addPolygon(segundaPlataforma);

	Polygon * tercerPlataforma = PolygonFactory::get_static_rectangle(5, 1, 10, 11, 0.1f, this);
	tercerPlataforma->setColor(200, 40, 200);
	this->addPolygon(tercerPlataforma);

	Polygon * bola = PolygonFactory::get_dynamic_circle(3, 16, 8, 2, this);
	this->addPolygon(bola);

	Polygon * laCajaLaCaja = PolygonFactory::get_dynamic_rectangle(2,2,10,16,0.1,this);
	laCajaLaCaja->setColor(54,12,25);
	this->addPolygon(laCajaLaCaja);

	//Polygon * newPolygon2 = PolygonFactory::get_static_rectangle(5, 1, 5, 4, 0.1f, this);
	//this->addPolygon(newPolygon2);

	//Polygon * newPolygon3 = PolygonFactory::get_static_regular_polygon(6, 10, 8, 8, 0.4f, this);
	//this->addPolygon(newPolygon3);

	/*

	Polygon * newPolygon4 = PolygonFactory::get_dynamic_trapezoid(2, 4, 3, 12, 8, 5, this);
	this->addPolygon(newPolygon4);
	this->addPolygon(PolygonFactory::get_static_trapezoid(7, 20, 3, 13, 3, 5,this));
	Polygon * newPolygon5 = PolygonFactory::get_dynamic_circle(3, 16, 8, 0.1f, this);
	this->addPolygon(newPolygon5);

	//Polygon * newPolygon6 = PolygonFactory::get_static_paralelogram(1.5, 0.5f, 3.14f/4, 1, 8, 0.1f, this);
	//this->addPolygon(newPolygon6);
}
*/

b2Vec2 * World::getWindowSize(){
	return this->SDLWindowSize;
}

bool World::isOutOfWorld(b2Vec2 position){
	return ((position.x <= (-2*this->Box2DWorldSize->x)) ||
			(position.y <= (-2*this->Box2DWorldSize->y)) ||
			(position.x >= (2*this->Box2DWorldSize->x)) ||
			(position.y >= (2*this->Box2DWorldSize->y)));
}

vector<Polygon *> World::getPolygonList(){
	return this->polygonList;
}

Resources * World::getResources(){
	return this->worldResources;
}

World::~World() {
	delete this->worldResources;
	delete this->contactListener;
	delete this->mainCharacter;

	delete this->gravity;
	delete this->box2DWorld;
	delete this->SDLWindowSize;

	for(auto *polygon : polygonList){
		delete polygon;
	}

	polygonList.clear();
}

