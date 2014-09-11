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
#include "engine/Animation.h"
#include "engine/ParticleEmiter.h"

#include <stdio.h>
#include <string>
#include <sstream>
#include "Box2D/Box2D.h"

using namespace std;

class pruebaEngine: public Game {
public:
	pruebaEngine(const char *title);
	virtual ~pruebaEngine();
private:
	virtual void update(unsigned int delta);
	virtual void render(Graphics *g);
	virtual void keyEvent(SDL_Event e);
	virtual void init();
	virtual void exit();

	b2World* world;
	b2Body* body;

	Image* testImage;
	SpriteSheet *spriteSheet;
	Image* subSprite;

	SpriteSheet *animationTest;
	Animation * animation;

	ParticleEmiter * particleE;

	float rotation;

	std::stringstream fpsText;
};

#endif /* PRUEBAENGINE_H_ */
