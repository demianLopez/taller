/*
 * MainMenu.h
 *
 *  Created on: 17/10/2014
 *      Author: demian
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "engine/GameState.h"
#include "engine/GUI/Button.h"
#include "engine/GUI/Label.h"
#include "engine/ParticleEmiter.h"
#include "engine/GUI/TextBox.h"

class MainMenu: public GameState {
public:
	MainMenu();
	virtual ~MainMenu();

	//Llamado al inicio de toda la api

	//llamado cuando entra al state
	//virtual void enter() {};
	//llamado cuando sale del state
	//virtual void leave() {};
	//Llamado al final de toda la api
	virtual void init(Game * game);
	virtual void exit(Game * game);
	virtual void render(Graphics *g, Game * game);
	virtual void update(unsigned int delta);
	virtual void keyEvent(SDL_Event e, Game * game);
private:
	int mouseX;
	int mouseY;

	void renderGUI(Graphics * g,  Game * game);
	Image * backgroundImage;

	ParticleEmiter * particleEmiter;

	//GUI

	Button * buttonConnect;
	Label * titleLabel;
	TextBox * userName;


};

#endif /* MAINMENU_H_ */
