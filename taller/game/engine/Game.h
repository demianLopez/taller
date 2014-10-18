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

<<<<<<< HEAD
	std::vector<GameState *> stateList;
=======
protected:
	virtual void render(Graphics *g) = 0;
	virtual void update(unsigned int delta) = 0;
	virtual void keyEvent(SDL_Event e) = 0;
	virtual void init() {
	}
	;
	virtual void exit() {
	}
	;
>>>>>>> e1937808fb9afca4669f6be726bfa2a8c61091d9
};

#endif /* GAME_H_ */
