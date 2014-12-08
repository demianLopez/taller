/*
 * ChangeState.cpp
 *
 *  Created on: 24/11/2014
 *      Author: demian
 */

#include "ChangeState.h"

#include <SDL2/SDL_events.h>
#include <sstream>

#include "../common/client_handler.h"
#include "../common/CommandCode.h"
#include "../common/Message.h"
#include "engine/Game.h"
#include "engine/Graphics.h"
#include "engine/GUI/Button.h"
#include "engine/Image.h"
#include "engine/ParticleEmiter.h"
#include "GameWorld.h"
#include "Global.h"
#include "Resources.h"

using std::string;

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
	g->setFont(Global::gameResources->getGuiFont());

	if(this->winLevel){
		g->setColor(0, 255, 0);
		g->drawText(300, 150, "Nivel Superado");
	} else {
		g->setColor(255, 0, 0);
		g->drawText(300, 150, "Juego Terminado");
	}

	g->setColor(255, 255, 255);

	for(int i = 0; i < playerCount; i++){

		std::stringstream score;
		score.clear();
		score.str("");
		score << scores[i];

		int hy = 250 + i * 30;
		g->drawText(150, hy, players[i].c_str());

		g->drawText(380, hy, score.str().c_str());
		bool online = playerConected[i];

		if(online){

			if(murio[i]){
				g->setColor(255, 0, 0);
				g->drawText(550, hy, "Game Over");
			} else {
				g->setColor(0, 255, 0);
				g->drawText(550, hy, "Conectado");
			}
		} else {
			g->setColor(255, 0, 0);
			g->drawText(550, hy, "Desconectado");
		}

		g->setColor(255, 255, 255);

	}

	if(imReady || tuMuerte){
		g->drawText(300, 520, "Esperando Jugadores");
	} else {
		g->resetGraphics();
		this->buttonConnect->render(g, mouseX, mouseY);
	}
}

void ChangeState::keyEvent(SDL_Event e, Game* game) {
	switch (e.type) {
	case SDL_MOUSEMOTION:
		this->mouseX = e.motion.x;
		this->mouseY = e.motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:


		if (this->buttonConnect->isClicked(mouseX, mouseY) && !imReady) {
			imReady = true;
			Message m;
			m.addCommandCode(PLAYER_READY);
			m.addEndChar();
			Global::client->send_message(&m);
		}

		break;
	}
}

void ChangeState::init(Game* game) {
	Global::changeState = this;
	this->buttonConnect = new Button("Listo");
	this->buttonConnect->setSize(256, 80);
	int pX = (game->getScreenWidth() - 256) / 2;
	this->buttonConnect->setPosition(pX, 480);

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

void ChangeState::setLevelData(string* players, int* scores, bool winLevel,
		int playerCount, bool* playerConected, bool * murio, bool tuMuerte) {

	this->players = players;
	this->scores = scores;
	this->winLevel = winLevel;
	this->playerCount = playerCount;
	this->playerConected = playerConected;
	this->murio = murio;
	this->tuMuerte = tuMuerte;
}

void ChangeState::enter() {
	if(winLevel){
		Global::gameResources->levelPass->play(1);
	} else {
		Global::gameResources->gameOver->play(1);
	}
	delete Global::gameWorld;
	Global::gameWorld = NULL;
	imReady = false;
}
