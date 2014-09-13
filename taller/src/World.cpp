/*
 * World.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "World.h"
#include "Resources.h"
#include "Personaje.h"

World::World() {
	this->worldResources = new Resources();
	this->mainCharacter = new Personaje();
}

void World::init(){
	this->loadWorld();
	this->generateWorld();
}

void World::loadResources(){
	this->worldResources->loadBackground("Resources/font1.png");
}

void World::loadWorld(){
	//world init!!! ACA ARMAR EL PARSEADO U LLAMAR AL OBJETO QUE PARSEA!
}

void World::generateWorld(){
	//GENERAR BOX2D
}

Resources * World::getResources(){
	return this->worldResources;
}

World::~World() {
	delete this->worldResources;
	delete this->mainCharacter;
}

