/*
 * GameState.h
 *
 *  Created on: 17/10/2014
 *      Author: demian
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Graphics.h"
#include "LibIncludes.h"

class Game;

class GameState {
public:
	GameState();
	virtual ~GameState();

	//Llamado al inicio de toda la api
	virtual void init(Game * game) = 0;
	//llamado cuando entra al state
	virtual void enter() {
	}
	;
	//llamado cuando sale del state
	virtual void leave() {
	}
	;
	//Llamado al final de toda la api
	virtual void exit(Game * game) = 0;

	virtual void render(Graphics *g, Game * game) = 0;
	virtual void update(unsigned int delta) = 0;
	virtual void keyEvent(SDL_Event e, Game * game) = 0;
};

#endif /* GAMESTATE_H_ */
