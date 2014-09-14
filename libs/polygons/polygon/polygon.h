/**
 polygon.h

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
#ifndef POLYGON_H_
#define POLYGON_H_

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

class Polygon {
public:
	static const int STATIC = 0;
	static const int DYNAMIC = 1;

private:
	int body_property;

protected:
	Polygon();
	virtual ~Polygon();

public:
	virtual void draw() = 0;
};

#endif /* POLYGON_H_ */
