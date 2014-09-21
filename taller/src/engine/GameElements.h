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

class GameElements {
public:
	GameElements();

	static SDL_Surface *gScreenSurface;
	static SDL_Renderer* gRenderer;

	virtual ~GameElements();

};

#endif /* GAMEELEMENTS_H_ */
