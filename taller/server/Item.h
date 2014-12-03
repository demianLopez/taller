/*
 * Item.h
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <Box2D/Box2D.h>

class Item {
public:
	Item(int index);
	int getIndex();
	bool isOnMap();
	void setOnMap(bool onMap);
	void setBox2DDefinitions(b2Body * body, b2Fixture * fixture);

	void putAt(float posX, float posY, int type);
	virtual ~Item();

private:
	int index;
	bool onMap;

	int type;

	b2Body * body;
	b2Fixture * fixture;
};

#endif /* ITEM_H_ */
