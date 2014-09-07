/**
 polygon_factory.h

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
#ifndef POLYGON_FACTORY_H_
#define POLYGON_FACTORY_H_

#include "../polygon/polygon.h"

class Polygon_factory {
private:
	Polygon_factory() {}
	virtual ~Polygon_factory() {}

public:
	static Polygon* get_regular_polygon(size_t sides, double scale,
			SDL_Color& color);
	static Polygon* get_rectangle(double height, double widht,
			SDL_Color& color);
	static Polygon* get_circle(double diameter, SDL_Color& color);

};

#endif /* POLYGON_FACTORY_H_ */
