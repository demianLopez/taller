/*
 * MainMenu.h
 *
 *  Created on: 17/10/2014
 *      Author: demian
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "engine/GameState.h"

class MainMenu: public GameState {
public:
	MainMenu();
	virtual ~MainMenu();

	//Llamado al inicio de toda la api

	//llamado cuando entra al state
	//virtual void enter() {};
	//llamado cuando sale del state
	//virtual void leave() {};
	//Llamado al final de toda la api
	virtual void init();
	virtual void exit();
	virtual void render(Graphics *g);
	virtual void update(unsigned int delta);
	virtual void keyEvent(SDL_Event e);

};

#endif /* MAINMENU_H_ */
