/*
 * World.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "Enemigo.h"
#include "Jugador.h"
#include "polygons/Polygon.h"

class Projectile;

using std::string;
using std::thread;
using std::mutex;

class Polygon;

class World {
public:
	World(b2Vec2* gravity);

	int updatesPerSecond;

	string* getWorldName();
	int getMaxPlayers();

	void setMapData(string* mapName, int maxPlayers);

	void setUnits(int wU, int hU);
	b2Vec2* getBox2DWorldSize();

	void worldStep(int delta);

	void addPolygon(Polygon* polygon);

	b2World* getBox2DWorld();
	vector<Polygon*> getPolygonList();

	bool isOutOfWorld(b2Vec2 position);

	bool isMainCharacterTouchingGround();

	void start();
	void stop();

	bool isOnLoop();

	void waitWorldThread();

	void addPlayer(Jugador* jugador, bool reconecting);
	void addEnemy(Enemigo * enemy);

	vector<Jugador*> getPlayerList();
	Jugador* getPlayer(int userIndex);

	void add_projectile(Projectile* p);
	vector<Enemigo*> getEnemyList();

	void releaseEntityIndex(int index);

	int getAvavibleIndex();

	virtual ~World();

	void sendToWorldPlayers(Message* m);

	void instantiatePlayer(Jugador* j, Client_handler* client);
	void instantiateEnemy(Enemigo * enemy, Client_handler * client);

	void requestKeyData(Jugador* j);
	void setMinPlayers(int minPlayers);

	bool isWaitingForPlayers();



	void sendWorldInfo(Client_handler* client);
	void checkPlayerCount();

	void nextLevel();
	void restartLevel();

	void nextSecond();

	void setCurrentLevelName(char* currentLevelName);
	void setNextLevelName(char* nextLevelName);
	void verifyLevelEndConditions();
private:
	void updateTiming(Jugador* j);
	void updatePolygon(Polygon* p);
	void updatePeople(Jugador* p);
	void updateEnemy(Enemigo* e);

	void sendUpdates();

	void initializePlayerBody(Jugador* player);

	void initializeEnemyBody(Enemigo * enemy);

	bool wordLoop;
	bool isRestarting;
	static void worldLoop(World * world);
	static void changeLevel(World * currentLevel, char * nextLevel, bool wonLevel);

	vector<Jugador*> playerList;
	vector<Enemigo*> enemyList;

	ContactListener* contactListener;

	thread worldThread;

	bool waitingPlayers;

	vector<Polygon*> polygonList;

	//BOX 2D
	b2World* box2DWorld;
	b2Vec2* gravity;

	b2Vec2* Box2DWorldSize;

	string* mapName;
	int maxPlayers;
	int minPlayers;

	int lastEntityIndex;

	mutex worldMutex;

	char * currentLevelName;
	char * nextLevelName;
};

#endif /* WORLD_H_ */
