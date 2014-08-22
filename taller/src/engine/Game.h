/*
 * Game.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "SDL.h"


class Game {
public:
	Game(const char* title);
	void setScreenSize(int height, int size);
	void start();
	virtual ~Game();
private:
	int height;
	int width;

	const char* title;

	SDL_Window *gWindow;
	SDL_Surface *gScreenSurface;

	void gameCicle();
	void gameClose();

protected:
	virtual void render() = 0;
	virtual void update(SDL_Event e) = 0;
};

#endif /* GAME_H_ */
