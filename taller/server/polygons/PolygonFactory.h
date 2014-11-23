/**
 Polygon_factory.h

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
#ifndef Polygon_FACTORY_H_
#define Polygon_FACTORY_H_

#include "Polygon.h"
#include "../World.h"

#include <Box2D/Box2D.h>
#include <stddef.h>

class PolygonFactory {
private:
	PolygonFactory() {
	}
	virtual ~PolygonFactory() {
	}

private:
	static Polygon* get_regular_polygon(size_t sides, double scale, double posX,
			double posY, double density, double rotation, int body_type,
			World * world);
	static Polygon* get_rectangle(double height, double widht, double posX,
			double posY, double density, double rotation, int body_type,
			World * world);
	static Polygon* get_circle(double diameter, double posX, double posY,
			double density, double rotation, int body_type, World * world);
	static Polygon* get_paralelogram(double base, double height, double angle,
			double posX, double posY, double density, double rotation,
			int body_type, World * world);
	static Polygon* get_trapezoid(double height, double base, double top,
			double angle, double posX, double posY, double density,
			double rotation, int body_type, World * world);

public:
	static Polygon* get_static_regular_polygon(size_t sides, double scale,
			double posX, double posY, double density, double rotation,
			World * world);
	static Polygon* get_static_rectangle(double height, double widht,
			double posX, double posY, double density, double rotation,
			World * world);
	static Polygon* get_static_circle(double diameter, double posX, double posY,
			double density, double rotation, World * world);
	static Polygon* get_static_paralelogram(double base, double height,
			double angle, double posX, double posY, double density,
			double rotation, World * world);
	static Polygon* get_static_trapezoid(double height, double base, double top,
			double angle, double posX, double posY, double density,
			double rotation, World * world);

	static Polygon* get_dynamic_regular_polygon(size_t sides, double scale,
			double posX, double posY, double density, double rotation,
			World * world);
	static Polygon* get_dynamic_rectangle(double height, double widht,
			double posX, double posY, double density, double rotation,
			World * world);
	static Polygon* get_dynamic_circle(double diameter, double posX,
			double posY, double density, double rotation, World * world);
	static Polygon* get_dynamic_paralelogram(double base, double height,
			double angle, double posX, double posY, double density,
			double rotation, World * world);
	static Polygon* get_dynamic_trapezoid(double height, double base,
			double top, double angle, double posX, double posY, double density,
			double rotation, World * world);
};

#endif /* Polygon_FACTORY_H_ */
