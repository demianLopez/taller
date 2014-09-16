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

class Resources;


class World {
public:
	World(int width, int height);
	void init();
	void loadResources();
	Resources * getResources();

	b2Vec2 box2DToSDL(b2Vec2 * box2DCoord);
	b2Vec2 SDLToBox2D(b2Vec2 * SDLCoord);

	void worldStep(int delta);

	Jugador * getMainCharacter();



	virtual ~World();
private:
	Resources * worldResources;
	Jugador * mainCharacter;

	void loadWorld();
	void generateWorld();

	//BOX 2D
	b2World * box2DWorld;
	b2Vec2  * gravity;

	b2Vec2 * SDLWindowSize;
	b2Vec2 * Box2DWorldSize;
};

#endif /* WORLD_H_ */
