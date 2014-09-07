/**
 model_polygon_factory.h

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
#ifndef MODEL_POLYGON_FACTORY_H_
#define MODEL_POLYGON_FACTORY_H_

#include "../model_polygon/model_polygon.h"

class Model_polygon_factory {

private:
	Model_polygon_factory() {}
	~Model_polygon_factory() {}

public:
	static Model_polygon* get_regular_polygon(size_t edges);
	static Model_polygon* get_rectangle(size_t height, size_t widht);
	static Model_polygon* get_circle(size_t height, size_t widht);

};

#endif /* MODEL_POLYGON_FACTORY_H_ */
