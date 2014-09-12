/**
 model_polygon_factory.cpp

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

#include "model_polygon_factory.h"
#include "../model_regular_polygon/model_regular_polygon.h"

Model_polygon* Model_polygon_factory::get_regular_polygon(size_t edges,
		double scale) {
	if (edges < 3) //No es un poligono valido
		return NULL;
	if (edges == 4) //Devuelvo un rectangulo de 1x1
		return get_rectangle(1, 1, scale);

	return new Model_regular_polygon(edges);
}

Model_polygon* Model_polygon_factory::get_rectangle(double height, double widht,
		double scale) {
	return NULL;
}

Model_polygon* Model_polygon_factory::get_circle(double diameter,
		double scale) {
	return NULL;
}
