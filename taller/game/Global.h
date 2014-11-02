/*
 * Global.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <client_handler.h>
#include <LevelState.h>
#include <MainMenu.h>
#include <Message.h>
#include <CommandCode.h>
#include <engine/Game.h>
#include <Resources.h>

class Global {
public:

	static Client_handler * client;
	static LevelState * levelState;
	static MainMenu * mainMenu;
	static Game * game;
	static GameWorld * gameWorld;
	static Resources * gameResources;

};

#endif /* GLOBAL_H_ */
