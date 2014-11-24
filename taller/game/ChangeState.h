/*
 * ChangeState.h
 *
 *  Created on: 24/11/2014
 *      Author: demian
 */

#ifndef CHANGESTATE_H_
#define CHANGESTATE_H_

#include "engine/GameState.h"
#include "engine/ParticleEmiter.h"
#include "engine/Image.h"

class ChangeState: public GameState {
public:
	ChangeState();
	virtual ~ChangeState();
private:
	void update(unsigned int delta);
	void render(Graphics *g, Game * game, unsigned int delta);
	void keyEvent(SDL_Event e, Game * game);
	void init(Game * game);
	void exit(Game * game);
	void enter();

	Image * backgroundImage;
	Image * tableImage;
	ParticleEmiter * particleEmiter;
};

#endif /* CHANGESTATE_H_ */
