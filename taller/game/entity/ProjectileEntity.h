/*
 * ProjectileEntity.h
 *
 *  Created on: 30/11/2014
 *      Author: demian
 */

#ifndef PROJECTILEENTITY_H_
#define PROJECTILEENTITY_H_

#include <entity/MovementEntity.h>

class ProjectileEntity: public MovementEntity {
public:
	ProjectileEntity(int index, int type);
	void render(Graphics * g, unsigned int delta);
	void initialize();
	void applyUpdate(UpdateRequest * u);
	virtual ~ProjectileEntity();
private:
	int type;
};

#endif /* PROJECTILEENTITY_H_ */
