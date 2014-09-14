/**
 model_polygon.cpp

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
#include "model_polygon.h"

#include <Box2D/Box2D.h>

Model_polygon::Model_polygon(int body_type) {
	if (body_type == STATIC)
	{
		this->body_type = b2_staticBody;
	} else { //Por defecto es dinamico (body_type == DYNAMIC)
		this->body_type = b2_dynamicBody;
	}
}

Model_polygon::~Model_polygon() {
	// TODO Auto-generated destructor stub
}
