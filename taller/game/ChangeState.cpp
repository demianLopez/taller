/*
 * ChangeState.cpp
 *
 *  Created on: 24/11/2014
 *      Author: demian
 */

#include <ChangeState.h>
#include "Global.h"

ChangeState::ChangeState() {
	// TODO Auto-generated constructor stub

}

ChangeState::~ChangeState() {
	// TODO Auto-generated destructor stub
}

void ChangeState::update(unsigned int delta) {
	this->particleEmiter->update(delta);
}

void ChangeState::render(Graphics* g, Game* game, unsigned int delta) {
	g->drawImage(backgroundImage);
	this->particleEmiter->render(g);
	g->drawImage(tableImage);
}

void ChangeState::keyEvent(SDL_Event e, Game* game) {
}

void ChangeState::init(Game* game) {
	this->backgroundImage = new Image("Resources/menuFont.jpeg");
	this->tableImage = new Image("Resources/ScoreTable.png");

	this->particleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->particleEmiter->setMaxParticles(40);
}

void ChangeState::exit(Game* game) {
	delete this->backgroundImage;
	delete this->particleEmiter;
	delete this->tableImage;
}

void ChangeState::enter() {
	delete Global::gameWorld;
	Global::gameWorld = NULL;
}
