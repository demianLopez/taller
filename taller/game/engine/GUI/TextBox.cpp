/*
 * TextBox.cpp
 *
 *  Created on: 26/10/2014
 *      Author: demian
 */

#include "TextBox.h"

TextBox::TextBox(const char * init) {
	this->text = std::string(init);
	this->lastUpdate = 0;
}

const char * TextBox::getText() {
	return this->text.c_str();
}

char TextBox::getLength() {
	return this->text.size();
}

void TextBox::render(Graphics * g) {
	g->setColor(0, 0, 0);
	g->drawFillRect(this->posX, this->posY, this->width, this->height);
	g->setColor(255, 255, 255);
	g->drawRect(this->posX - 2, this->posY - 2, this->width + 4,
			this->height + 4);

	int tY = height / 2 - 22 + posY;
	int tX = 5 + posX;

	std::string auxText(text);

	if (lastUpdate > 500) {
		auxText += "|";
	}
	if (auxText.size() != 0) {
		g->drawText(tX, tY, auxText.c_str());
	}
	auxText.clear();
}

void TextBox::update(int delta) {
	lastUpdate += delta;
	lastUpdate = lastUpdate % 1000;
}

void TextBox::addChar(char c) {
	if (this->text.size() > 20) {
		return;
	}

	this->text += c;
}

void TextBox::deleteChar() {
	if (this->text.size() > 0) {
		this->text = this->text.erase(text.size() - 1, 1);
	}
}

TextBox::~TextBox() {
	this->text.clear();
}

