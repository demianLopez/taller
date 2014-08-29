/*
 * pruebaEngine.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "pruebaEngine.h"
#include "engine/Graphics.h"

pruebaEngine::pruebaEngine(const char *title) : Game(title) {
	this->testImage = NULL;
}

void pruebaEngine::init(){
	this->testImage = new Image("Resources/a.png");
	this->spriteSheet = new SpriteSheet("Resources/tilea3.png", 64 ,64);
}

void pruebaEngine::exit(){
	delete testImage;
	delete spriteSheet;
}

void pruebaEngine::render(Graphics *g){
	g->drawImage(testImage, 0, 50);
	g->drawFillRect(20, 20, 20, 20);
	g->drawRect(60, 20, 20, 20);

	Image * subSprite = spriteSheet->getSubImage(0, 0);
	g->drawImage(subSprite, 20, 20);

	g->setColor(255, 0, 0);
	g->drawLine(20, 60, 80, 60);
	g->drawPoint(90, 60);
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

