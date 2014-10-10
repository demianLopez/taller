/*
 * SnowBross.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef SNOWBROSS_H_
#define SNOWBROSS_H_

#include "engine/Game.h"
#include "engine/Image.h"

class Graphics;
class World;
class ParticleEmiter;

class SnowBross : public Game {
public:
	SnowBross( const char *pTitle);
	void setWorld(World * world);
	virtual ~SnowBross();
private:
	virtual void update(unsigned int delta);
	virtual void render(Graphics *g);
	virtual void keyEvent(SDL_Event e);
	virtual void init();
	virtual void exit();


	Image * worldImage;

	World * gameWorld;
	ParticleEmiter * backParticleEmiter;
	ParticleEmiter * frontParticleEmiter;

	float zoomScale;
	float maxZoomScale;
	float minZoomScale;

};

#endif /* SNOWBROSS_H_ */
