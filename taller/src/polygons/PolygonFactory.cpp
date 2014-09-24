/**
 PolygonFactory.cpp

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

#include "PolygonFactory.h"
#include "RegularPolygon.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Circle.h"
#include "Paralelogram.h"

Polygon* PolygonFactory::get_regular_polygon(size_t sides, double scale, double posX, double posY,
		double density, double rotation, int body_type, World * world) {
	return new RegularPolygon(sides, scale, posX, posY, body_type, density, rotation, world);
}

Polygon* PolygonFactory::get_rectangle(double height, double widht, double posX, double posY,
		double density, double rotation, int body_type, World * world) {
	return new Rectangle(widht, height, density, posX, posY, rotation, body_type, world);
}

Polygon* PolygonFactory::get_circle(double diameter, double posX, double posY,
		double density, double rotation, int body_type, World * world) {
	return new Circle(diameter, posX, posY, density, rotation, body_type, world);

}

Polygon * PolygonFactory::get_trapezoid(double height, double base, double top, double posX, double posY,
		double density, double rotation, int body_type, World * world){
	return new Trapezoid(height, base, top, posX, posY, density, rotation, body_type, world);
}

Polygon * PolygonFactory::get_paralelogram(double base, double height, double angle, double posX,
		double posY, double density, double rotation, int body_type,	World * world){
	return new Paralelogram(base, height, angle, posX, posY, density, rotation, body_type, world);
}
//STATIC --------------------------------------

Polygon* PolygonFactory::get_static_regular_polygon(size_t sides, double scale, double posX, double posY,
		double density, double rotation, World * world) {
	return PolygonFactory::get_regular_polygon(sides, scale, posX, posY, density, rotation, Polygon::STATIC, world);
}

Polygon* PolygonFactory::get_static_rectangle(double height,
		double widht, double posX, double posY, double density, double rotation, World * world) {
	return get_rectangle(height, widht, posX, posY, density, rotation, Polygon::STATIC, world);
}

Polygon* PolygonFactory::get_static_circle(double diameter,
		double posX, double posY, double density, double rotation, World * world) {
	return get_circle(diameter, posX, posY, density, rotation, Polygon::STATIC, world);

}

Polygon* PolygonFactory::get_static_trapezoid(double height, double base,
		double top, double posX, double posY, double density, double rotation, World* world){
	return get_trapezoid(height, base, top, posX, posY, density, rotation, Polygon::STATIC, world);
}

Polygon* PolygonFactory::get_static_paralelogram(double base, double height, double angle, double posX,
			double posY, double density, double rotation, World * world){
	return get_paralelogram(base, height, angle, posX, posY, density, rotation, Polygon::STATIC, world);
}
//Dynamic-------------------------------------------------

Polygon* PolygonFactory::get_dynamic_regular_polygon(size_t sides, double scale, double posX, double posY,
		double density, double rotation, World * world) {
	return get_regular_polygon(sides, scale, posX, posY, density, rotation, Polygon::DYNAMIC, world);

}

Polygon* PolygonFactory::get_dynamic_rectangle(double height,
		double widht, double posX, double posY, double density, double rotation, World * world) {
	return get_rectangle(height, widht, posX, posY, density, rotation, Polygon::DYNAMIC, world);
}

Polygon* PolygonFactory::get_dynamic_circle(double diameter,
		double posX, double posY, double density, double rotation, World * world){
	return get_circle(diameter, posX, posY, density, rotation, Polygon::DYNAMIC, world);
}

Polygon * PolygonFactory::get_dynamic_trapezoid(double height, double base,
		double top, double posX, double posY, double density, double rotation, World * world){
	return get_trapezoid(height, base, top, posX, posY, density, rotation, Polygon::DYNAMIC, world);
}

Polygon * PolygonFactory::get_dynamic_paralelogram(double base, double height, double angle, double posX,
		double posY, double density, double rotation, World * world){
	return get_paralelogram(base, height, angle, posX, posY, density, rotation, Polygon::DYNAMIC, world);

}
