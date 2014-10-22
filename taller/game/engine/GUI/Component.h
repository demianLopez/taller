/*
 * Component.h
 *
 *  Created on: 18/10/2014
 *      Author: demian
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

class Component {
public:
	Component();

	void setPosition(int x, int y);
	void setSize(int width, int height);

	bool isClicked(int xClick, int yClick);

	virtual ~Component();
protected:
	int posX;
	int posY;

	int width;
	int height;
};

#endif /* COMPONENT_H_ */
