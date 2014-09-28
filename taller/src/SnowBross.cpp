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
	this->backParticleEmiter = NULL;
	this->frontParticleEmiter = NULL;
}

void SnowBross::init(){
	//ADICIONALES!
	//Estos son extras, despues hay que cambiarlos!
	this->backParticleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->backParticleEmiter->setMaxParticles(20);

	this->frontParticleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->frontParticleEmiter->setMaxParticles(20);
}

void SnowBross::setWorld(World * world){
	this->gameWorld = world;
}

void SnowBross::exit(){
	delete this->gameWorld;
	delete this->backParticleEmiter;
	delete this->frontParticleEmiter;
}

void SnowBross::render(Graphics *g){
	Resources * resources = this->gameWorld->getResources();

	//Dibujamos fondo!
	Image * backImage = resources->getBackground();
	if(backImage != NULL){
		g->drawImage(backImage, 0, 0, this->getScreenWidth(), this->getScreenHeight());
	}

	this->backParticleEmiter->render(g);

	vector<Polygon *> polList = this->gameWorld->getPolygonList();
	for(auto *polygon : polList){
		polygon->render(g);
	}


	g->drawAtCenter(true);
	b2Vec2 playerPos = this->gameWorld->getMainCharacter()->getBody()->GetPosition();
	playerPos = gameWorld->box2DToSDL(&playerPos);

	b2Vec2 playerSize = this->gameWorld->getMainCharacter()->getSize();
	playerSize =  this->gameWorld->box2DToSDLSize(&playerSize);

	g->drawAnimation(gameWorld->getMainCharacter()->getAnimation(resources), playerPos.x, playerPos.y, playerSize.x, playerSize.y);

	this->frontParticleEmiter->render(g);
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
				if(this->gameWorld->isMainCharacterTouchingGround()){
					this->gameWorld->getMainCharacter()->jump();
				}
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

	this->backParticleEmiter->update(delta);
	this->frontParticleEmiter->update(delta);
	this->gameWorld->worldStep(delta);
	this->gameWorld->getMainCharacter()->update();

}

SnowBross::~SnowBross() {

}

