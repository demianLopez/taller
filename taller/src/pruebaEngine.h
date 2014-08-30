/*
 * pruebaEngine.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef PRUEBAENGINE_H_
#define PRUEBAENGINE_H_

#include "engine/Game.h"
#include "engine/Image.h"
#include "engine/SpriteSheet.h"
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

class pruebaEngine: public Game {
public:
	pruebaEngine(const char *title);
	virtual ~pruebaEngine();
private:
	virtual void update(SDL_Event e, unsigned int delta);
	virtual void render(Graphics *g);
	virtual void init();
	virtual void exit();

	Image* testImage;
	SpriteSheet *spriteSheet;
	Image* subSprite;

	float rotation;

	std::stringstream fpsText;
};

#endif /* PRUEBAENGINE_H_ */
