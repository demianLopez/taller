/*
 * SnowBross.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "SnowBross.h"
#include "MainMenu.h"
#include "LevelState.h"

SnowBross::SnowBross(const char *pTitle) : Game(pTitle) {

}

void SnowBross::initializeGameStates(){
	this->addState(new MainMenu());

	//TEMPORAL HASTA TENER SERVIDOR FUNCIONAL!
	LevelState * lS = new LevelState();
	GameWorld * gW = new GameWorld(VectorXY(50, 30));

	lS->setWorld(gW);

	this->addState(lS);



	this->enterState(0);
}

SnowBross::~SnowBross() {

}

