/**
 level_object.h

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
#ifndef LEVEL_OBJECT_H_
#define LEVEL_OBJECT_H_

class Level_object {
protected:
	bool _is_alive;

public:
	Level_object();

	bool is_alive();

	virtual ~Level_object();
};

#endif /* LEVEL_OBJECT_H_ */
