/**
 model_polygon.h

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
#ifndef MODEL_POLYGON_H_
#define MODEL_POLYGON_H_

class Model_polygon {

public:
	static const int STATIC = 0;
	static const int DYNAMIC = 1;

protected:
	int body_type;
	int scale;

public:
	Model_polygon(int body_type);
	virtual ~Model_polygon();

	void rotate(double angle);
	void move(double x_units,double y_units);
};

#endif /* MODEL_POLYGON_H_ */
