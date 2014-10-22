/*
 * Label.h
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "Component.h"
#include "../Graphics.h"

class Label: public Component {
public:
	Label(const char * text);

	void render(Graphics * g);

	virtual ~Label();
private:
	const char * text;
};

#endif /* LABEL_H_ */
