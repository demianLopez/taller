/*
 * pruebaEngine.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "pruebaEngine.h"
#include "engine/Graphics.h";

pruebaEngine::pruebaEngine(const char *title) : Game(title) {


}

void pruebaEngine::init(){
	this->testImage = new Image("Resources/a.png");
}

void pruebaEngine::render(Graphics *g){
	g->drawImage(testImage);
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

