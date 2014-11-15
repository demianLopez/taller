/*
 * enemy_factory.cpp
 *
 *  Created on: 15/11/2014
 *      Author: hige
 */

#include "enemy_factory.h"
#include "move_patterns/standar_movement_strategy.h"

Enemy* Enemy_factory::get_enemy() {
	return new Enemy();
}

Enemy* Enemy_factory::get_standar_enemy() {
	Enemy* standar = get_enemy();
//	standar.set_weapon(new standar_weapon());
//	standar.set_movement(new Standar_movement_strategy());
	return standar;
}
