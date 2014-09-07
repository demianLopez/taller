/**
 regular_polygon.cpp

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
#include "regular_polygon.h"
#include "../model_polygon_factory/model_polygon_factory.h"

Regular_polygon::Regular_polygon(size_t edges, double scale,
		SDL_Color& colora) {
	this->model = Model_polygon_factory::get_regular_polygon(edges);
}

Regular_polygon::~Regular_polygon() {
	delete this->model;
}
