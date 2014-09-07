/**
 regular_polygon.h

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
#ifndef REGULAR_POLYGON_H_
#define REGULAR_POLYGON_H_

#include "../polygon/polygon.h"
#include "../model_polygon/model_polygon.h"

class Regular_polygon: public Polygon {
private:
	Model_polygon* model;

public:
	Regular_polygon(size_t edges, double scale, SDL_Color& colora);
	virtual ~Regular_polygon();

	void draw() {}
};

#endif /* REGULAR_POLYGON_H_ */
