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
	this->spriteSheet = NULL;
	this->subSprite = NULL;
	this->animationTest = NULL;
	this->animation = NULL;

	rotation = 0;
}

void pruebaEngine::init(){
	this->testImage = new Image("Resources/a.png");
	this->spriteSheet = new SpriteSheet("Resources/tilea3.png", 64 ,64);
	this->subSprite = spriteSheet->getSubImage(0, 1);

	this->animationTest = new SpriteSheet("Resources/anim.png", 21, 40);
	this->animation = new Animation();

	for(int x = 0; x < 8; x++){
		this->animation->addFrame(this->animationTest->getSubImage(x, 0), 75);
	}

}

void pruebaEngine::exit(){
	delete testImage;
	delete spriteSheet;
	delete subSprite;
	delete animationTest;
	delete animation;
}

void pruebaEngine::render(Graphics *g){
	g->drawImage(testImage, 0, 50);

	g->drawRect(60, 20, 20, 20);

	g->drawImage(this->subSprite, 20, 20, rotation);

	g->setColor(255, 0, 0);

	g->drawLine(20, 60, 80, 60);
	g->drawPoint(90, 60);

	fpsText.str("");
	fpsText<<this->getFPS()<< " FPS";

	g->drawText(10, 10, fpsText.str().c_str());
	rotation+=0.05f;
	g->drawFillRect(400, 20, 30, 20);

	g->drawAnimation(this->animation, 100, 100);
}

void pruebaEngine::update(SDL_Event e, unsigned int delta){
	if( e.type == SDL_KEYDOWN){
		if(e.key.keysym.sym == SDLK_UP){
			cout<<"Presiono arriba";
		}
	}
}

pruebaEngine::~pruebaEngine() {
	// TODO Auto-generated destructor stub
}

