/**
 box2d_polygon_factory.h

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
#ifndef BOX2D_POLYGON_FACTORY_H_
#define BOX2D_POLYGON_FACTORY_H_

class Box2d_Polygon_factory {
private:
	Box2d_Polygon_factory() {};
	~Box2d_Polygon_factory() {};

public:
	static b2PolygonShape get_regular_polygon(int edges);
};

#endif /* BOX2D_POLYGON_FACTORY_H_ */
