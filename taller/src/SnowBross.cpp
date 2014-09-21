/*
 * SnowBross.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "SnowBross.h"
#include "engine/Game.h"
#include "engine/Graphics.h"
#include "engine/LibIncludes.h"
#include "engine/ParticleEmiter.h"
#include "engine/Image.h" //Provisional
#include "Personaje.h"

#include "World.h"
#include "Resources.h"

SnowBross::SnowBross(const char *pTitle) : Game(pTitle) {
	this->gameWorld = NULL;
	this->particleEmiter = NULL;
	vx = new short int[4];
	vy = new short int[4];

	vx[0] = 30;
	vx[1] = 40;
	vx[2] = 55;
	vx[3] = 35;

	vy[0] = 200;
	vy[1] = 180;
	vy[2] = 220;
	vy[3] = 300;

}

void SnowBross::init(){
	this->gameWorld = new World(this->getScreenWidth(), this->getScreenHeight());

	this->gameWorld->init();
	this->gameWorld->loadResources();


	//ADICIONALES!
	//Estos son extras, despues hay que cambiarlos!
	this->particleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->particleEmiter->setMaxParticles(20);
}

void SnowBross::exit(){
	delete this->gameWorld;
	delete this->particleEmiter;
}

void SnowBross::render(Graphics *g){
	Resources * resources = this->gameWorld->getResources();

	//Dibujamos fondo!
	Image * backImage = resources->getBackground();
	if(backImage != NULL){
		g->drawImage(backImage, 0, 0, this->getScreenWidth(), this->getScreenHeight());
	}
	this->particleEmiter->render(g);


	g->drawFillRect(200, 540, 400, 60);


	g->drawAtCenter(true);
	b2Vec2 playerPos = this->gameWorld->getMainCharacter()->getBody()->GetPosition();

	playerPos = gameWorld->box2DToSDL(&playerPos);

	g->drawAnimation(gameWorld->getMainCharacter()->getAnimation(resources), playerPos.x, playerPos.y, -this->gameWorld->getMainCharacter()->getBody()->GetAngle() * 57);

	g->drawFillPolygon(vx, vy, 4, 0, 255, 0);

}

void SnowBross::keyEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				this->gameWorld->getMainCharacter()->setMovingLeft(true);
				break;

			case SDLK_RIGHT:
				this->gameWorld->getMainCharacter()->setMovingRight(true);
				break;

			case SDLK_UP:
				this->gameWorld->getMainCharacter()->jump();
				break;
		}
		return;
	}

	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				this->gameWorld->getMainCharacter()->setMovingLeft(false);
				break;

			case SDLK_RIGHT:
				this->gameWorld->getMainCharacter()->setMovingRight(false);
				break;


		}
	}

}


void SnowBross::update(unsigned int delta){
	this->particleEmiter->update(delta);
	this->gameWorld->worldStep(delta);
	this->gameWorld->getMainCharacter()->update();
}

SnowBross::~SnowBross() {

}

