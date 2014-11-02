/*
 * World.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <Box2D/Box2D.h>
#include "Jugador.h"
#include <vector>
#include "polygons/Polygon.h"
#include "ContactListener.h"
#include <thread>

using std::thread;

class Polygon;

class World {
public:
	World(b2Vec2 * gravity);

	void setUnits(int wU, int hU);
	b2Vec2 * getBox2DWorldSize();

	void worldStep(int delta);

	void addPolygon(Polygon * polygon);

	b2World * getBox2DWorld();
	vector<Polygon *> getPolygonList();

	bool isOutOfWorld(b2Vec2 position);

	bool isMainCharacterTouchingGround();

	void start();
	void stop();

	bool isOnLoop();

	void waitWorldThread();

	void addPlayer(Jugador * jugador);
	vector<Jugador*> getPlayerList();
	Jugador * getPlayer(int userIndex);

	virtual ~World();
private:

	bool wordLoop;
	static void worldLoop(World * world);

	vector<Jugador*> playerList;

	ContactListener *contactListener;

	thread worldThread;

	vector<Polygon*> polygonList;

	//BOX 2D
	b2World * box2DWorld;
	b2Vec2 * gravity;

	b2Vec2 * Box2DWorldSize;
};

#endif /* WORLD_H_ */
