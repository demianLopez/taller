/**
 character.cpp

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
#include "character.h"

Character::Character() {
	// TODO Auto-generated constructor stub
}

void Character::set_weapon(Weapon* weapon) {
	weapons.push(weapon);
}

void Character::reduce_life() {
}

Character::~Character() {
	while (!weapons.empty()) {
		Weapon* weapon = weapons.top();
		weapons.pop();
		delete weapon;
	}
}

Projectile* Character::fire() {
	Projectile* p = weapons.top()->fire();
	if (weapons.top()->is_empty()) {
		delete weapons.top();
		weapons.pop();
	}
	return p;
}

void Character::collide(Level_object* object) {
}
