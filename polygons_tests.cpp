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

#include <Box2D/Box2D.h>
#include "libs/polygons/polygons.h"

int main() {
	b2Vec2 gravity(0,9.8);
	b2World* world = new b2World(gravity);

	Model_polygon* pol1 = Model_polygon_factory::get_static_regular_polygon(4,
			2, *world);
	Model_polygon* pol2 = Model_polygon_factory::get_dynamic_regular_polygon(3,
			2, *world);
	Model_polygon* circle = Model_polygon_factory::get_dynamic_circle(2, 1,
			*world);

	delete pol1;
	delete pol2;
	delete circle;
	delete world;
	return 0;
}
