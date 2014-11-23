/**
 fire.h

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
#ifndef FIRE_H_
#define FIRE_H_

#define SPAWN_LEFT 0
#define SPAWN_RIGHT 1
#define SPAWN_BOTH 2

#include "dmg_projectile.h"

class Fire: public Dmg_projectile {

private:
	char spawn_direction = SPAWN_BOTH;

private:
	Fire(char spawn_direction);
	void spread();

public:
	Fire();
	virtual ~Fire();
};

#endif /* FIRE_H_ */
