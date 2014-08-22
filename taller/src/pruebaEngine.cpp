/*
 * pruebaEngine.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "pruebaEngine.h"

pruebaEngine::pruebaEngine(const char *title) : Game(title) {
	// TODO Auto-generated constructor stub

}

void pruebaEngine::render(){

}

void pruebaEngine::update(SDL_Event e){
	if( e.type == SDL_KEYDOWN){
		if(e.key.keysym.sym == SDLK_UP){
			cout<<"Presiono arriba";
		}
	}
}

pruebaEngine::~pruebaEngine() {
	// TODO Auto-generated destructor stub
}

