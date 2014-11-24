/**
 snow_banana.cpp

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

#include "snow_banana.h"

#include <list>

#include "../../bonus_items/bonus/snow_counter.h"
#include "../../moving_objects/character.h"

using std::list;

Snow_banana::Snow_banana() {
	// TODO Auto-generated constructor stub

}

Snow_banana::~Snow_banana() {
	// TODO Auto-generated destructor stub
}

void Snow_banana::collide(Character& character) {
	character.add_bonus(new Snow_counter());

	list<Bonus*> bonus = character.get_asigned_bonus();

	int i = 0;
	int total_counters = 0;

	while (i < bonus.size()) {
		if (bonus[i]->get_type() == SNOW_COUNTER) {
			total_counters++;
		}
	}

	if (total_counters > 4) {
		character.die();
		//TODO: Spawn snowball
	}

}
