/*
 * Game.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "LibIncludes.h"
#include "GameElements.h"

class Graphics;

class Game {
public:
	Game(const char* title);
	void setScreenSize(int height, int size);
	unsigned int getFPS();
	unsigned int getElapsedTime();
	void setMaxFPS(int maxFPS);

	bool start();
	void endGame();

	virtual ~Game();
private:
	int height;
	int width;

	const char* title;

	bool quit;
	SDL_Window *gWindow;
	SDL_Surface *gScreenSurface;
	SDL_Renderer* gRenderer;
	TTF_Font *gFont;

	void gameCicle();
	void gameClose();

	int fps;
	int renderCount;

	unsigned int lastUpdateTime;
	unsigned int lastRenderTime;
	unsigned int lastFPSUpdateTime;

	bool limitedFPS;
	int maxFPS;

	bool shuldWeRender();

protected:
	virtual void render(Graphics *g) = 0;
	virtual void update(SDL_Event e, unsigned int delta) = 0;
	virtual void init() { };
	virtual void exit() { };
};

#endif /* GAME_H_ */
