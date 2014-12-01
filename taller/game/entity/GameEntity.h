/*
 * GameEntity.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include "../../common/CommandCode.h"
#include "../VectorXY.h"

class GameWorld;
class Graphics;
class UpdateRequest;

class GameEntity {
public:
	GameEntity(int index);
	virtual ~GameEntity();
	virtual void render(Graphics * g, unsigned int dela) = 0;
	virtual void update(unsigned int delta) = 0;
	virtual void addUpdateRequest(UpdateRequest * u,
			unsigned int currentTime) = 0;

	bool isActive();

	void setRotation(float rotation);

	void setWorld(GameWorld * gameWorld);
	virtual void initialize() = 0;
	void setPosition(float x, float y);
	VectorXY getPosition();

	void setType(EntityType type);

	int getIndex();
	void setActive(bool active);
private:
	int entityIndex;
	virtual void setedActive(bool active) { };

protected:
	VectorXY position;
	GameWorld * gameWorld;
	float rotation;

	EntityType type;

	bool active;

};

#endif /* GAMEENTITY_H_ */
