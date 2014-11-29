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
#include "engine/GUI/Button.h"

class ChangeState: public GameState {
public:
	ChangeState();
	virtual ~ChangeState();
	void setLevelData(string * players, int * scores, bool winLevel, int playerCount, bool * playerConected);
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

	Button * buttonConnect;

	int mouseX;
	int mouseY;

	bool imReady;

	bool * playerConected;
	string * players;
	int * scores;
	bool winLevel;
	int playerCount;

};

#endif /* CHANGESTATE_H_ */
