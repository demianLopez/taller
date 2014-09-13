/*
 * World.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef WORLD_H_
#define WORLD_H_

class Resources;
class Personaje;

class World {
public:
	World();
	void init();
	void loadResources();
	Resources * getResources();
	virtual ~World();
private:
	Resources * worldResources;
	Personaje * mainCharacter;


	void loadWorld();
	void generateWorld();
};

#endif /* WORLD_H_ */
