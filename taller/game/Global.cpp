/*
 * Global.cpp
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#include "Global.h"

Client_handler * Global::client;
LevelState * Global::levelState;
MainMenu * Global::mainMenu;
SnowBross * Global::game;
GameWorld * Global::gameWorld;
Resources * Global::gameResources;
ChangeState* Global::changeState;
int Global::serverUpdateTiming;

int Global::playerLife;
int Global::playerScore;
