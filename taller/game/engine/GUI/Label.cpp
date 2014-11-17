/*
 * Label.cpp
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#include "Label.h"

Label::Label(const char * text) {
	this->text = text;
}

void Label::render(Graphics * g) {
	int tY = height / 2 - 22 + posY;
	int tX = (width - strlen(this->text) * 14) / 2 + posX;

	g->drawText(tX, tY, this->text);
}

Label::~Label() {
}

