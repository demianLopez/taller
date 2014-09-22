/**
 model_regular_polygon.h

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
#ifndef MODEL_REGULAR_POLYGON_H_
#define MODEL_REGULAR_POLYGON_H_

#include <stddef.h>
#include <Box2D/Box2D.h>

#include "Polygon.h"

class RegularPolygon: public Polygon {
public:
	RegularPolygon(size_t edges, double scale, double posX, double posY, int body_type,
			double density, World * world);
	virtual ~RegularPolygon();
private:
	void setSDLVertex(size_t sides, b2Vec2* vertex);
};

#endif /* MODEL_REGULAR_POLYGON_H_ */
