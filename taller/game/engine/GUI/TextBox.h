/*
 * TextBox.h
 *
 *  Created on: 26/10/2014
 *      Author: demian
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include "Component.h"
#include <engine/Graphics.h>
#include <string.h>

class TextBox: public Component {
public:
	TextBox(const char * init);
	void render(Graphics * g);
	void update(int delta);
	void addChar(char c);
	void deleteChar();
	virtual ~TextBox();

	const char * getText();
	char getLength();
private:
	std::string text;
	int lastUpdate;
};

#endif /* TEXTBOX_H_ */
