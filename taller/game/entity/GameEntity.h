/*
 * GameEntity.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <engine/Graphics.h>

class GameEntity {
public:
	GameEntity(int index);
	virtual ~GameEntity();
	virtual void render(Graphics * g) = 0;
private:
	int index;
};

#endif /* GAMEENTITY_H_ */
