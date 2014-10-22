/*
 * Button.h
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Component.h"
#include "../Graphics.h"
#include "../SpriteSheet.h"
#include "../Image.h"

class Button : public Component{
public:
	Button(const char * text);
	void render(Graphics * g, int mouseX, int mouseY);
	virtual ~Button();

private:
	const char * text;
	Image * normal;
	Image * hover;
	SpriteSheet * btnSprite;
};

#endif /* BUTTON_H_ */
