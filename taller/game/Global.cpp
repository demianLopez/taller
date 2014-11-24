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
int Global::serverUpdateTiming;

int Global::playerLife = 4;
