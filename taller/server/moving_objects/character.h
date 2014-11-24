/**
 character.h

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
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <list>

class Weapon;
class Projectile;
#include "moving_object.h"
#include "../weapons/weapon.h"
#include "../bonus_items/bonus/bonus.h"

#include <stack>

class Character: public Moving_object {
protected:

	std::stack<Weapon*> weapons;
	std::list<Bonus*> bonus;
	int energy;

public:
	Character();

	void set_weapon(Weapon* weapon);
	Projectile* fire();
	void reduce_life();

	void add_bonus(Bonus* bonus);
	std::list<Bonus*> get_asigned_bonus();

	void die();

	int get_energy();

	~Character();
};

#endif /* CHARACTER_H_ */
