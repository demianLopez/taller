/**
 fire_launcher.h

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
#ifndef FIRE_LAUNCHER_H_
#define FIRE_LAUNCHER_H_

#include "standar_weapon.h"

class Fire_launcher: public Standar_weapon {
protected:
	virtual Projectile* get_projectile();

public:
	Fire_launcher(World* world);
	virtual ~Fire_launcher();
};

#endif /* FIRE_LAUNCHER_H_ */
