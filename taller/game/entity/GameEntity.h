/*
 * GameEntity.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <engine/Graphics.h>
#include <VectorXY.h>
#include <GameWorld.h>
#include <UpdateRequest.h>

class GameEntity {
public:
	GameEntity(int index);
	virtual ~GameEntity();
	virtual void render(Graphics * g) = 0;
	virtual void update(UpdateRequest * u) = 0;

	void setRotation(float rotation);

	void setWorld(GameWorld * gameWorld);
	virtual void initialize() = 0;
	void setPosition(float x, float y);
	VectorXY getPosition();

	int getIndex();
private:
	int entityIndex;

protected:
	VectorXY position;
	GameWorld * gameWorld;
	float rotation;
};

#endif /* GAMEENTITY_H_ */
