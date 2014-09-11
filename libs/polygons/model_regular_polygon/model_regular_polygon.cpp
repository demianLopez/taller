/**
 model_regular_polygon.cpp

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
#define _USE_MATH_DEFINES
#include <math.h>

#include "model_regular_polygon.h"

Model_regular_polygon::Model_regular_polygon(size_t edges) {
	double perimeter = 2 * M_PI;
	double segment_size = perimeter / edges;

	//parametrizar


}

Model_regular_polygon::~Model_regular_polygon() {
	// TODO Auto-generated destructor stub
}

