/*
 * GameElements.cpp
 *
 *  Created on: 23/8/2014
 *      Author: EscDemi
 */

#include "GameElements.h"

SDL_Surface * GameElements::gScreenSurface = NULL;
SDL_Renderer * GameElements::gRenderer = NULL;
TTF_Font * GameElements::gFont = NULL;

GameElements::GameElements() {
	// TODO Auto-generated constructor stub

}

Graphics * GameElements::getGraphicsInstance() {
	return new Graphics(GameElements::gFont);
}

GameElements::~GameElements() {
	// TODO Auto-generated destructor stub
}

