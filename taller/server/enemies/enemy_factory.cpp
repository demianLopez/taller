/**
 enemy_factory.cpp

 Copyright 2014 Gaston Martinez Gaston.martinez.90@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses
 */

#include "enemy_factory.h"
#include "move_patterns/standar_movement_strategy.h"
#include "../weapons/standar_weapon.h"

Enemy* Enemy_factory::get_enemy() {
	return new Enemy();
}

Enemy* Enemy_factory::get_standar_enemy() {
	Enemy* standar = get_enemy();
	standar->set_weapon(new Standar_weapon());
//	standar.set_movement(new Standar_movement_strategy());
	return standar;
}
