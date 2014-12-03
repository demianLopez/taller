/*
 * Item.h
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <Box2D/Box2D.h>
#include "Jugador.h"
#include "B2DAfterChange.h"


class Item: public B2DAfterChange {
public:
	Item(int index);
	int getIndex();
	bool isOnMap();
	void setOnMap(bool onMap);
	void setBox2DDefinitions(b2Body * body, b2Fixture * fixture);

	void putAt(float posX, float posY, int type);
	virtual ~Item();

	void consumir(Jugador * player);
	void change();

private:
	int index;
	bool onMap;

	int type;

	b2Body * body;
	b2Fixture * fixture;

	Jugador * playerAfected;
};

#endif /* ITEM_H_ */
