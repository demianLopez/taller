/*
 * Paralelogram.h
 *
 *  Created on: 22/9/2014
 *      Author: EscDemi
 */

#ifndef PARALELOGRAM_H_
#define PARALELOGRAM_H_

#include "Polygon.h"
#include <Box2D/Box2D.h>

class Paralelogram: public Polygon {
public:
	Paralelogram(double base, double height, double angle, double posX,
			double posY, double density, double rotation, int body_type,
			World * world);

	virtual ~Paralelogram();
private:
	void setVertex(b2Vec2 * vertex);
	void define_vertex(double base, double height, double angle,
			b2Vec2* vertex);
};

#endif /* PARALELOGRAM_H_ */
