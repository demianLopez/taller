/*
 * pruebaEngine.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef PRUEBAENGINE_H_
#define PRUEBAENGINE_H_

#include "engine/Game.h"
using namespace std;

class pruebaEngine: public Game {
public:
	pruebaEngine(const char *title);
	virtual ~pruebaEngine();
private:
	virtual void render();
	virtual void update(SDL_Event e);

};

#endif /* PRUEBAENGINE_H_ */
