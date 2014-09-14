/**
 polygons_tests.cpp

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

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

#include "libs/polygons/model_polygon/model_polygon.h"
#include "libs/polygons/model_polygon_factory/model_polygon_factory.h"

using std::cout;
using std::endl;

int main() {
	b2Vec2 gravity(0, 9.8);
	b2World* world = new b2World(gravity);

	Model_polygon* pol1 = Model_polygon_factory::get_static_regular_polygon(4,
			2, 1, *world);
	Model_polygon* pol2 = Model_polygon_factory::get_dynamic_regular_polygon(3,
			2, 1, *world);
	Model_polygon* pol3 = Model_polygon_factory::get_dynamic_regular_polygon(3,
			2, 1, *world);
	Model_polygon* circle = Model_polygon_factory::get_dynamic_circle(2, 1, 1,
			*world);
	Model_polygon* rectangle = Model_polygon_factory::get_static_rectangle(4, 2,
			1, *world);
	Model_polygon* paralelogram = NULL; //Model_polygon_factory::get_static_paralelogram(4,2, 1, *world);
	Model_polygon* trapezoid = NULL; //Model_polygon_factory::get_static_trapezoid(4,2, 1, *world);

	std::cout << "Crear Poligono regular estatico de 4 "
			<< (pol1 ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Poligono regular dinamico de 3 "
			<< (pol2 ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Poligono regular dinamico de 2 "
			<< (pol3 ? "ERROR" : "OK") << std::endl;

	std::cout << "Crear Circlulo de 1 " << (circle ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Crear Rectangulo de 2 " << (rectangle ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Crear Paralelogramo de 1 " << (paralelogram ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Crear Trapezoide de 1 " << (trapezoid ? "OK" : "ERROR")
			<< std::endl;

	delete pol1;
	delete pol2;
	delete circle;
	delete rectangle;
	delete paralelogram;
	delete trapezoid;
	delete world;
	return 0;
}
