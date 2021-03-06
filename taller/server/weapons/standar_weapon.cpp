/**
 standar_weapon.cpp

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
#include "standar_weapon.h"

Standar_weapon::Standar_weapon(World* world) :
		Weapon(world) {
	remaining_bullets = -1;
}

Projectile* Standar_weapon::get_projectile() {
	return NULL; //FIXME
}

Standar_weapon::~Standar_weapon() {
}

void Standar_weapon::launch(Projectile* p) {
	p->apply_force(10,(this->direction == LEFT) ? -10:10);
}
