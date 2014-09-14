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

#include <SDL2/SDL.h>
#include "libs/polygons/polygons.h"

int main() {
	SDL_Color color;
	color.r = 3;
	color.g = 4;
	color.b = 66;
	auto world;
	Polygon* pol1 = Polygon_factory::get_regular_polygon(4, 2, color,world,Polygon::STATIC);
	Polygon* pol2 = Polygon_factory::get_regular_polygon(3, 2, color,world,Polygon::DYNAMIC);
	Polygon* circle = Polygon_factory::get_circle(2,color,world,Polygon::DYNAMIC);


	delete pol;
	return 0;
}
