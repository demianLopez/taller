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

class Global {
public:

	static Client_handler * client;
	static LevelState * levelState;
	static MainMenu * mainMenu;

};

#endif /* GLOBAL_H_ */
