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

#include "World.h"
#include "Resources.h"

SnowBross::SnowBross(const char *pTitle) : Game(pTitle) {
	this->gameWorld = NULL;
	this->particleEmiter = NULL;
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

	b2Vec2 playerPos = this->gameWorld->getCharacterPosition();
	playerPos = gameWorld->box2DToSDL(&playerPos);

	g->drawAnimation(resources->getPlayerAnimationRight(), playerPos.x, playerPos.y);


}

void SnowBross::keyEvent(SDL_Event e){

}


void SnowBross::update(unsigned int delta){
	this->particleEmiter->update(delta);
	this->gameWorld->worldStep(delta);
}

SnowBross::~SnowBross() {

}

