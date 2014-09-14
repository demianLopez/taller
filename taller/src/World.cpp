/*
 * World.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "World.h"
#include "Resources.h"
#include "Personaje.h"

World::World(int width, int height) {
	this->worldResources = new Resources();
	this->mainCharacter = NULL;
	this->SDLWindowSize = new b2Vec2(width, height);
	this->box2DWorld = NULL;
	this->gravity = NULL;
	this->Box2DWorldSize = NULL;
	this->mainCharacter = NULL;
}

void World::init(){
	this->loadWorld();
	this->generateWorld();
}

void World::loadResources(){
	this->worldResources->loadBackground("Resources/font1.png");
	this->worldResources->loadAnimations();
}

void World::loadWorld(){
	//world init!!! ACA ARMAR EL PARSEADO U LLAMAR AL OBJETO QUE PARSEA!
	this->gravity = new b2Vec2(0, - 10);
	this->Box2DWorldSize = new b2Vec2(10, 10);
}

b2Vec2 World::box2DToSDL(b2Vec2 * box2DCoord){
	float sdlX = box2DCoord->x/Box2DWorldSize->x * SDLWindowSize->x;
	float sdlY = SDLWindowSize->y - box2DCoord->y/Box2DWorldSize->y * SDLWindowSize->y;
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

Personaje * World::getMainCharacter(){
	return this->mainCharacter;
}

void World::generateWorld(){
	//GENERAR BOX2D
	this->box2DWorld = new b2World(*gravity);


	this->mainCharacter = new Personaje(box2DWorld);

	//WORLD!

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);

	b2Body* groundBody = box2DWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(10, 1);

	groundBody->CreateFixture(&groundBox, 0.0f);


}


Resources * World::getResources(){
	return this->worldResources;
}

World::~World() {
	delete this->worldResources;
	delete this->mainCharacter;

	delete this->gravity;
	delete this->box2DWorld;
	delete this->SDLWindowSize;
}

