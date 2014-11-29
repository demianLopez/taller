/**
 projectile.h

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
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

class Character;

#include "../../moving_objects/moving_object.h"
#include "../../moving_objects/character.h"

class Projectile: public Moving_object {
public:
	Projectile();
	virtual void collide(Character& character);
	virtual ~Projectile();
};

#endif /* PROJECTILE_H_ */
