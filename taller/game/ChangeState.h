/*
 * ChangeState.h
 *
 *  Created on: 24/11/2014
 *      Author: demian
 */

#ifndef CHANGESTATE_H_
#define CHANGESTATE_H_

#include <string>

#include "engine/GameState.h"

class Button;
class ParticleEmiter;

class ChangeState: public GameState {
public:
	ChangeState();
	virtual ~ChangeState();
	void setLevelData(std::string * players, int * scores, bool winLevel,
			int playerCount, bool * playerConected);
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

	bool* playerConected;
	std::string* players;
	int* scores;
	bool winLevel;
	int playerCount;

};

#endif /* CHANGESTATE_H_ */
