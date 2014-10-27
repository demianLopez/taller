/*
 * MainMenu.cpp
 *
 *  Created on: 17/10/2014
 *      Author: demian
 */

#include "MainMenu.h"
#include "engine/Game.h"


MainMenu::MainMenu() {
	this->buttonConnect = NULL;
	this->mouseX = 0;
	this->mouseY = 0;
	this->backgroundImage = NULL;
}

void MainMenu::init(Game * game){
	this->buttonConnect = new Button("Conectar");
	this->buttonConnect->setSize(256, 80);
	int pX = (game->getScreenWidth() - 256)/2;
	this->buttonConnect->setPosition(pX, 500);

	this->backgroundImage = new Image("Resources/menuFont.jpeg");

	this->particleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->particleEmiter->setMaxParticles(40);

	this->titleLabel = new Label("Servidor");
	this->titleLabel->setSize(200, 50);
	pX = (game->getScreenWidth() - 200)/2;
	this->titleLabel->setPosition(pX, 80);

	this->userName = new TextBox("Username");
	this->userName->setSize(530, 40);
	pX = (game->getScreenWidth() - 530)/2;
	this->userName->setPosition(pX, 135);
}

void MainMenu::exit(Game * game){
	delete buttonConnect;
	delete particleEmiter;
	delete titleLabel;
}

void MainMenu::render(Graphics * g,  Game * game){
	g->drawImage(this->backgroundImage);

	this->particleEmiter->render(g);
	this->renderGUI(g, game);
}

void MainMenu::renderGUI(Graphics * g, Game * game){
	g->setColor(0, 200, 50);
	g->drawFillRect(100, 75, game->getScreenWidth() - 200, game->getScreenHeight()-200);
	g->setColor(255, 255, 255);
	g->drawRect(98, 73, game->getScreenWidth() - 196, game->getScreenHeight()-196);
	g->drawRect(125, 125, game->getScreenWidth() - 250, game->getScreenHeight() - 275);
	g->setColor(0,0,0);

	this->titleLabel->render(g);
	this->buttonConnect->render(g, mouseX, mouseY);
	this->userName->render(g);
}

void MainMenu::update(unsigned int delta){
	this->particleEmiter->update(delta);
	this->userName->update(delta);
}

void MainMenu::keyEvent(SDL_Event e, Game * game){
	switch(e.type)
	{
	case SDL_MOUSEMOTION:
		this->mouseX = e.motion.x;
		this->mouseY = e.motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:

		if(this->buttonConnect->isClicked(mouseX, mouseY)){
			game->enterState(1);
		}

		break;
	case SDL_KEYDOWN:
		unsigned char k = e.key.keysym.sym;
		//TODO: agregar mas ascii para el textBox!
		//OJO, los ascii de SDL no todos coinciden con los ascii reales!

		if((k >= 97 && k <= 122) || k == 32){
			this->userName->addChar(k);
		}

		if(k == 8){

			this->userName->deleteChar();
		}
	}
}

MainMenu::~MainMenu() {
	// TODO Auto-generated destructor stub
}

