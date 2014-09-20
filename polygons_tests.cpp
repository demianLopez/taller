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

void test_create() {
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
	Model_polygon* static_paralelogram = NULL;
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
	Model_polygon* dynamic_paralelogram = NULL;
	Model_polygon* dynamic_trapezoid =
			Model_polygon_factory::get_dynamic_trapezoid(2, 2, 1, 1, *world);

	/*Test create*/

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

	/*Test initial position*/

	b2Vec2 origin = b2Vec2(0, 0);

	std::cout << "Poligono regular estatico de 4 en posicion 0,0 "
			<< (static_regular_1->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Poligono regular estatico de 6 en posicion 0,0 "
			<< (static_regular_2->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Circulo estatico de 2 en posicion 0,0 "
			<< (static_circle->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Rectangulo estatico de 4x2 en posicion 0,0 "
			<< (static_rectangle->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	/*std::cout << "Paralelogramo estatico en posicion 0,0 "
	 << (static_paralelogram->get_position() == origin ? "OK" : "ERROR")
	 << std::endl;*/
	std::cout << "Trapezoide estatico en posicion 0,0 "
			<< (static_trapezoid->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;

	std::cout << "Poligono regular dinamico de 3 en posicion 0,0 "
			<< (dynamic_regular_1->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Poligono regular dinamico de 6 en posicion 0,0 "
			<< (dynamic_regular_2->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Circulo dinamico de 2 en posicion 0,0 "
			<< (dynamic_circle->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Rectangulo dinamico de 4x2 en posicion 0,0 "
			<< (dynamic_rectangle->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	/*std::cout << "Paralelogramo dinamico en posicion 0,0 "
	 << (dynamic_paralelogram->get_position() == origin ? "OK" : "ERROR")
	 << std::endl;*/
	std::cout << "Trapezoide dinamico en posicion 0,0 "
			<< (dynamic_trapezoid->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;

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
}

void test_fall() {
	b2Vec2 gravity(0, -200);
	b2World* world = new b2World(gravity);
	world->SetGravity(gravity);

	Model_polygon* static_regular_1 =
			Model_polygon_factory::get_static_regular_polygon(4, 2, 1, *world);
	Model_polygon* static_regular_2 =
			Model_polygon_factory::get_static_regular_polygon(6, 2, 1, *world);

	Model_polygon* dynamic_regular_1 =
			Model_polygon_factory::get_dynamic_regular_polygon(4, 2, 1, *world);
	Model_polygon* dynamic_regular_2 =
			Model_polygon_factory::get_dynamic_regular_polygon(6, 2, 1, *world);

	float32 timeStep = 2;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	b2Vec2 origin = b2Vec2(0, 0);

	world->Step(timeStep, velocityIterations, positionIterations);

	std::cout << "Poligono regular estatico de 4 cae de la posicion 0,0 "
			<< (static_regular_1->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Poligono regular estatico de 6 cae de la posicion 0,0 "
			<< (static_regular_2->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;

	std::cout << "Poligono regular dinamico de 3 cae de la posicion 0,0 "
			<< (dynamic_regular_1->get_position() == origin ? "ERROR" : "OK")
			<< std::endl;
	std::cout << "Poligono regular dinamico de 6 cae de la posicion 0,0 "
			<< (dynamic_regular_2->get_position() == origin ? "ERROR" : "OK")
			<< std::endl;

	delete static_regular_1;
	delete static_regular_2;

	delete dynamic_regular_1;
	delete dynamic_regular_2;

	delete world;
}

void test_move() {
	b2Vec2 gravity(0, 0);
	b2World* world = new b2World(gravity);
	world->SetGravity(gravity);

	Model_polygon* static_regular_1 =
			Model_polygon_factory::get_static_regular_polygon(4, 2, 1, *world);
	Model_polygon* static_regular_2 =
			Model_polygon_factory::get_static_regular_polygon(6, 2, 1, *world);

	Model_polygon* dynamic_regular_1 =
			Model_polygon_factory::get_dynamic_regular_polygon(4, 2, 1, *world);
	Model_polygon* dynamic_regular_2 =
			Model_polygon_factory::get_dynamic_regular_polygon(6, 2, 1, *world);

	float32 timeStep = 2;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	b2Vec2 origin = b2Vec2(0, 0);

	static_regular_1->set_velocity(200, 200);
	static_regular_2->set_velocity(200, 200);
	dynamic_regular_1->set_velocity(200, 200);
	dynamic_regular_2->set_velocity(200, 200);

	world->Step(timeStep, velocityIterations, positionIterations);

	std::cout << "Poligono regular estatico de 4 se mueve de la posicion 0,0 "
			<< (static_regular_1->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;
	std::cout << "Poligono regular estatico de 6 se mueve de la posicion 0,0 "
			<< (static_regular_2->get_position() == origin ? "OK" : "ERROR")
			<< std::endl;

	std::cout << "Poligono regular dinamico de 3 se mueve de la posicion 0,0 "
			<< (dynamic_regular_1->get_position() == origin ? "ERROR" : "OK")
			<< std::endl;
	std::cout << "Poligono regular dinamico de 6 se mueve de la posicion 0,0 "
			<< (dynamic_regular_2->get_position() == origin ? "ERROR" : "OK")
			<< std::endl;

	delete static_regular_1;
	delete static_regular_2;

	delete dynamic_regular_1;
	delete dynamic_regular_2;

	delete world;
}

int main() {
	test_create();
	test_fall();
	test_move();
	return 0;
}
