/*
 * Game.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>
#include "LibIncludes.h"
#include "GameElements.h"
#include <string>
#include <sstream>
#include "GameState.h"

class Graphics;

class Game {
public:
	Game(const char* title);
	void setScreenSize(int width, int height);
	unsigned int getFPS();
	unsigned int getElapsedTime();
	void setMaxFPS(int maxFPS);

	void start();
	bool instantiate();
	void endGame();

	void addState(GameState * state);
	void enterState(int id);

	int getScreenHeight();
	int getScreenWidth();

	void showFPS(bool showFPS);

	virtual ~Game();
private:
	int height;
	int width;

	const char* title;

	GameState * currentState;
	bool changingState;
	int nextState;

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

	bool sfps; //SHOW FPS
	std::stringstream fpsText;

	std::vector<GameState *> stateList;

};

#endif /* GAME_H_ */
