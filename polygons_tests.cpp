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

	Model_polygon* invalid_1 =
			Model_polygon_factory::get_dynamic_regular_polygon(2, 2, 1, *world);

	std::cout << "Crear Poligono regular dinamico de 2 "
			<< (invalid_1 ? "ERROR" : "OK") << std::endl;

	Model_polygon* static_regular_1 =
			Model_polygon_factory::get_static_regular_polygon(4, 2, 1, *world);
	Model_polygon* static_regular_2 =
			Model_polygon_factory::get_static_regular_polygon(6, 2, 1, *world);
	Model_polygon* static_circle = Model_polygon_factory::get_static_circle(2,
			1, *world);
	Model_polygon* static_rectangle =
			Model_polygon_factory::get_static_rectangle(4, 2, 1, *world);
	Model_polygon* static_paralelogram = NULL; //Model_polygon_factory::get_static_paralelogram(4,2, 1, *world);
	Model_polygon* static_trapezoid =
			Model_polygon_factory::get_static_trapezoid(2, 2, 1, 1, *world);

	Model_polygon* dynamic_regular_1 =
			Model_polygon_factory::get_dynamic_regular_polygon(3, 2, 1, *world);
	Model_polygon* dynamic_regular_2 =
			Model_polygon_factory::get_dynamic_regular_polygon(6, 2, 1, *world);
	Model_polygon* dynamic_circle = Model_polygon_factory::get_dynamic_circle(2,
			1, *world);
	Model_polygon* dynamic_rectangle =
			Model_polygon_factory::get_dynamic_rectangle(4, 2, 1, *world);
	Model_polygon* dynamic_paralelogram = NULL; //Model_polygon_factory::get_static_paralelogram(4,2, 1, *world);
	Model_polygon* dynamic_trapezoid =
			Model_polygon_factory::get_dynamic_trapezoid(2, 2, 1, 1, *world);

	std::cout << "Crear Poligono regular estatico de 4 "
			<< (static_regular_1 ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Poligono regular estatico de 6 "
			<< (static_regular_2 ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Circulo estatico de 2 "
			<< (static_circle ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Rectangulo estatico de 4x2 "
			<< (static_rectangle ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Paralelogramo estatico "
			<< (static_paralelogram ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Trapezoide estatico "
			<< (static_trapezoid ? "OK" : "ERROR") << std::endl;

	std::cout << "Crear Poligono regular dinamico de 3 "
			<< (dynamic_regular_1 ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Poligono regular dinamico de 6 "
			<< (dynamic_regular_2 ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Circulo dinamico de 2 "
			<< (dynamic_circle ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Rectangulo dinamico de 4x2 "
			<< (dynamic_rectangle ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Paralelogramo dinamico "
			<< (dynamic_paralelogram ? "OK" : "ERROR") << std::endl;
	std::cout << "Crear Trapezoide dinamico "
			<< (dynamic_trapezoid ? "OK" : "ERROR") << std::endl;

	delete static_regular_1;
	delete static_regular_2;
	delete static_circle;
	delete static_rectangle;
	delete static_paralelogram;
	delete static_trapezoid;

	delete dynamic_regular_1;
	delete dynamic_regular_2;
	delete dynamic_circle;
	delete dynamic_rectangle;
	delete dynamic_paralelogram;
	delete dynamic_trapezoid;

	delete world;
	return 0;
}
