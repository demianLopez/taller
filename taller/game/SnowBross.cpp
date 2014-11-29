/*
 * SnowBross.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "SnowBross.h"
#include "MainMenu.h"
#include "LevelState.h"
#include "ChangeState.h"
#include "Global.h"
#include "Resources.h"

SnowBross::SnowBross(const char *pTitle) :
		Game(pTitle) {
	this->closingGame = false;
}

void SnowBross::initializeGameStates() {
	this->addState(new MainMenu());
	this->addState(new LevelState());
	this->addState(new ChangeState());

	this->enterState(0);
}

void SnowBross::initGame() {
	Resources * resources = new Resources();
	resources->loadAnimations();

	Global::gameResources = resources;
}
bool SnowBross::isClosing() {
	return this->closingGame;
}
void SnowBross::exitGame() {
	//Global::client->stop();
	delete Global::gameResources;
	closingGame = true;
}

SnowBross::~SnowBross() {

}

