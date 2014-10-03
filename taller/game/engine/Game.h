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
#include <string>
#include <sstream>

class Graphics;

class Game {
public:
	Game(const char* title);
	void setScreenSize(int width, int height);
	void setFrapImageSize(int width, int height);
	unsigned int getFPS();
	unsigned int getElapsedTime();
	void setMaxFPS(int maxFPS);

	bool start();
	bool instantiate();
	void endGame();

	int getScreenHeight();
	int getScreenWidth();

	int getFrapImageHeight();
	int getFrapImageWidth();



	void showFPS(bool showFPS);

	virtual ~Game();
private:
	int height;
	int width;

	int frapImageWidth;
	int frapImageHeight;

	const char* title;

	bool quit;
	SDL_Window *gWindow;
	SDL_Surface *gScreenSurface;
	SDL_Renderer* gRenderer;
	TTF_Font *gFont;

	bool gameCicle();
	void gameClose();

	int fps;
	int renderCount;

	unsigned int lastUpdateTime;
	unsigned int lastRenderTime;
	unsigned int lastFPSUpdateTime;

	bool limitedFPS;
	int maxFPS;

	bool sfps; //SHOW FPS
	std::stringstream fpsText;

protected:
	virtual void render(Graphics *g) = 0;
	virtual void update(unsigned int delta) = 0;
	virtual void keyEvent(SDL_Event e) = 0;
	virtual void init() { };
	virtual void exit() { };
};

#endif /* GAME_H_ */
