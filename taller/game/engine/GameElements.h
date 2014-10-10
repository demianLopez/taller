/*
 * GameElements.h
 *
 *  Created on: 23/8/2014
 *      Author: EscDemi
 */

#ifndef GAMEELEMENTS_H_
#define GAMEELEMENTS_H_

#include <iostream>
#include "LibIncludes.h"
#include "Graphics.h"

class GameElements {
public:
	GameElements();

	static Graphics * getGraphicsInstance();
	static SDL_Surface *gScreenSurface;
	static SDL_Renderer* gRenderer;
	static TTF_Font *gFont;

	virtual ~GameElements();

};

#endif /* GAMEELEMENTS_H_ */
