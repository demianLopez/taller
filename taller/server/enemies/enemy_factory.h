/*
 * enemy_factory.h
 *
 *  Created on: 15/11/2014
 *      Author: hige
 */

#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_

#include "enemy.h"

class Enemy_factory {
private:
	static Enemy* get_enemy();
public:
	static Enemy* get_standar_enemy();
};

#endif /* ENEMY_FACTORY_H_ */
