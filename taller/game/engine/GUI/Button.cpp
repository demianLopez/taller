/*
 * Button.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "Button.h"

Button::Button(const char * text) {
	this->posX = 0;
	this->posY = 0;

	this->width = 0;
	this->height = 0;

	this->text = text;

	this->btnSprite = new SpriteSheet("Resources/btn_tiled.png", 256, 80);
	this->normal = this->btnSprite->getSubImage(0, 0);
	this->hover = this->btnSprite->getSubImage(0, 1);
}

void Button::render(Graphics * g, int mouseX, int mouseY) {
	bool hoverX = mouseX > posX && mouseX < (posX + width);
	bool hoverY = mouseY > posY && mouseY < (posY + height);

	int dx = 0;
	int dy = 0;

	if (hoverX && hoverY) {
		g->drawImage(hover, posX, posY, width, height);
		dx = 2;
		dy = 2;
	} else {
		g->drawImage(normal, posX, posY, width, height);
	}

	int tY = height / 2 - 22 + posY + dx;
	int tX = (width - strlen(this->text) * 14) / 2 + posX + dy;

	g->drawText(tX, tY, this->text);
}

Button::~Button() {
	delete normal;
	delete hover;
	delete btnSprite;
}

