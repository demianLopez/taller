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

Polygon* PolygonFactory::get_regular_polygon(size_t sides, double scale, double posX, double posY,
		double density, int body_type, World * world) {

	/*
	if (sides < 3) //No es un poligono valido
		return NULL;
	if (sides == 4) //Devuelvo un rectangulo de 1x1
		return get_rectangle(scale, scale, 0, 0, density, body_type, world);

	*/

	return new RegularPolygon(sides, scale, posX, posY, density, body_type, world);
}

Polygon* PolygonFactory::get_rectangle(double height, double widht, double posX, double posY,
		double density, int body_type, World * world) {
	return new Rectangle(height, widht, density, posX, posY, body_type, world);
}

Polygon* PolygonFactory::get_circle(double diameter, double posX, double posY,
		double density, int body_type, World * world) {
	return new Circle(diameter, posX, posY, density, body_type, world);

}

Polygon* PolygonFactory::get_static_regular_polygon(size_t sides, double scale, double posX, double posY,
		double density, World * world) {
	return PolygonFactory::get_regular_polygon(sides, scale, posX, posY, density, Polygon::STATIC, world);
}

Polygon* PolygonFactory::get_static_rectangle(double height,
		double widht, double posX, double posY, double density, World * world) {
	return get_rectangle(height, widht, posX, posY, density, Polygon::STATIC, world);
}

Polygon* PolygonFactory::get_static_circle(double diameter,
		double posX, double posY, double density, World * world) {
	return get_circle(diameter, posX, posY, density, Polygon::STATIC, world);

}

Polygon * PolygonFactory::get_trapezoid(double height, double base, double top, double posX, double posY,
		double density, int body_type, World * world){

	return new Trapezoid(height, base, top, posX, posY, density, body_type, world);
}

Polygon* PolygonFactory::get_static_trapezoid(double height, double base,
		double top, double posX, double posY, double density, World* world){
	return get_trapezoid(height, base, top, posX, posY, density, Polygon::STATIC, world);
}


Polygon* PolygonFactory::get_dynamic_regular_polygon(size_t sides,
		double scale, double density, World * world) {
	return NULL;

}

Polygon* PolygonFactory::get_dynamic_rectangle(double height,
		double widht, double density, World * world) {
	return NULL;

}

Polygon* PolygonFactory::get_dynamic_circle(double diameter,
		double scale, double density, World * world) {
	return NULL;

}
