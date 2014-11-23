/**
 moving_object.h

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
#ifndef MOVING_OBJECT_H_
#define MOVING_OBJECT_H_

#include "../level_objects/level_object.h"
#include "move_patterns/move_pattern.h"

class Moving_object: public Level_object {
	Move_pattern* move_pattern;

public:
	Moving_object();
	void set_movement(Move_pattern* pattern);
	virtual ~Moving_object();
};

#endif /* MOVING_OBJECT_H_ */
