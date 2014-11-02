/*
 * LevelState.h
 *
 *  Created on: 17/10/2014
 *      Author: demian
 */

#ifndef LEVELSTATE_H_
#define LEVELSTATE_H_

#include "engine/GameState.h"
#include <iostream>

#include "engine/Image.h"
#include "engine/SpriteSheet.h"
#include "engine/Animation.h"
#include "engine/Graphics.h"
#include "engine/Game.h"
#include "engine/Graphics.h"
#include "engine/LibIncludes.h"
#include "engine/ParticleEmiter.h"
#include "engine/Image.h" //Provisional
#include "GameWorld.h"

class LevelState: public GameState {
public:
	LevelState();
	virtual ~LevelState();

	void setWorld(GameWorld * world);
private:
	virtual void update(unsigned int delta);
	virtual void render(Graphics *g, Game * game);
	virtual void keyEvent(SDL_Event e, Game * game);
	virtual void init(Game * game);
	virtual void exit(Game * game);
	void enter();

	int centroX;
	int centroY;

	Image * worldImage;
	Image * backgroundImage;

	GameWorld * gameWorld;

	ParticleEmiter * backParticleEmiter;
	ParticleEmiter * frontParticleEmiter;

	Animation * lightAnimation;
	SpriteSheet * spriteLightAnimation;
	int lightAnimationX;

	float zoomScale;
	float maxZoomScale;
	float minZoomScale;
};

#endif /* LEVELSTATE_H_ */
