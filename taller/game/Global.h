/*
 * Global.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "../common/client_handler.h"
#include "LevelState.h"
#include "MainMenu.h"
#include "../common/Message.h"
#include "../common/CommandCode.h"
#include "SnowBross.h"
#include "Resources.h"
#include "ChangeState.h"

class Global {
public:

	static int serverUpdateTiming;
	static Client_handler * client;
	static LevelState * levelState;
	static MainMenu * mainMenu;
	static ChangeState * changeState;
	static SnowBross * game;
	static GameWorld * gameWorld;
	static Resources * gameResources;

	static int playerLife;
	static int playerScore;

};

#endif /* GLOBAL_H_ */
