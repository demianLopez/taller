/*
 * SnowBross.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "SnowBross.h"
#include "MainMenu.h"
#include "LevelState.h"
#include "Global.h"
#include "Resources.h"

SnowBross::SnowBross(const char *pTitle) : Game(pTitle) {

}

void SnowBross::initializeGameStates(){
	this->addState(new MainMenu());
	this->addState(new LevelState());

	this->enterState(0);
}

void SnowBross::initGame(){
	Resources * resources = new Resources();
	resources->loadAnimations();

	Global::gameResources = resources;
}

void SnowBross::exitGame(){
	delete Global::gameResources;
}

SnowBross::~SnowBross() {

}

