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
}

void MainMenu::init(Game * game){
	this->buttonConnect = new Button("Conectar");
	this->buttonConnect->setSize(256, 80);
	int pX = (game->getScreenWidth() - 256)/2;
	this->buttonConnect->setPosition(pX, 500);
}

void MainMenu::exit(Game * game){
	delete buttonConnect;
}

void MainMenu::render(Graphics * g){
	this->renderGUI(g);
}

void MainMenu::renderGUI(Graphics * g){
	this->buttonConnect->render(g, mouseX, mouseY);
}

void MainMenu::update(unsigned int delta){

}

void MainMenu::keyEvent(SDL_Event e){
	switch(e.type)
	{
	case SDL_MOUSEMOTION:
		this->mouseX = e.motion.x;
		this->mouseY = e.motion.y;
		break;
	}
}

MainMenu::~MainMenu() {
	// TODO Auto-generated destructor stub
}

