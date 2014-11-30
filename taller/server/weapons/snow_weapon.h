/**
 snow_weapon.h

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
#ifndef SNOW_WEAPON_H_
#define SNOW_WEAPON_H_

#include "standar_weapon.h"

class Snow_weapon: public Standar_weapon {
protected:
	virtual Projectile* get_projectile();

public:
	Snow_weapon(World* world);
	virtual ~Snow_weapon();
};

#endif /* SNOW_WEAPON_H_ */
