/*
 * World.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "Box2D/Box2D.h"
#include "Jugador.h"
#include <vector>
#include "polygons/Polygon.h"

class Resources;
class Polygon;


class World {
public:
	World(int width, int height);
	void init();
	void loadResources();
	Resources * getResources();

	b2Vec2 box2DToSDL(b2Vec2 * box2DCoord);
	b2Vec2 SDLToBox2D(b2Vec2 * SDLCoord);

	//
	b2Vec2 box2DToSDLSize(b2Vec2 * box2DCoord);

	b2Vec2 * getWindowSize();

	void worldStep(int delta);

	void addPolygon(Polygon * polygon);

	Jugador * getMainCharacter();

	b2World * getBox2DWorld();

	vector<Polygon *> getPolygonList();

	bool isOutOfWorld(b2Vec2 position);


	virtual ~World();
private:
	Resources * worldResources;
	Jugador * mainCharacter;

	void loadWorld();
	void generateWorld();

	vector<Polygon*> polygonList;

	//BOX 2D
	b2World * box2DWorld;
	b2Vec2  * gravity;

	b2Vec2 * SDLWindowSize;
	b2Vec2 * Box2DWorldSize;
};

#endif /* WORLD_H_ */
