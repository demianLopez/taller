/*
 * Paralelogram.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

/*
 * Paralelogram.cpp
 *
 * Created on: 22/9/2014
 * Author: EscDemi
 */
#include <polygons/Paralelogram.h>
#include <math.h>
void Paralelogram::define_vertex(double base, double height, double angle,
		b2Vec2* vertex) {
	double y_height;
	double x_def;
	double x_base;
	if (angle == 0) {
		x_base = base / 2;
		y_height = height / 2;
		x_def = 0;
	} else {
		y_height = height / 2;
		x_def = height / tan(angle);
		x_base = (base + x_def) / 2;
	}
	vertex[0] = b2Vec2(-x_base, -y_height);
	vertex[1] = b2Vec2(base - x_base, -y_height);
	vertex[2] = b2Vec2(x_base, y_height);
	vertex[3] = b2Vec2(x_base - base, y_height);
}
Paralelogram::Paralelogram(double base, double height, double angle,
		double posX, double posY, double density, double rotation,
		int body_type, World * world) :
		Polygon(body_type) {
	b2Vec2* vertex = new b2Vec2[4];
	this->define_vertex(base, height, angle, vertex);
	b2PolygonShape polygon_shape;
	polygon_shape.Set(vertex, 4); //seteo los vertices del poligono
	b2FixtureDef body_fixture;
	body_fixture.shape = &polygon_shape;
	body_fixture.density = density;
	body_fixture.friction = friction;
	b2BodyDef body_definition;
	body_definition.angle = rotation;
	if (body_type == Polygon::STATIC) {
		body_definition.type = b2_staticBody;
	} else {
		body_definition.type = b2_dynamicBody;
	}
	body_definition.position.Set(posX, posY); //seteo posicion base
	this->create_body(&body_definition, &body_fixture, world);
	this->setVertex(vertex);
	delete[] vertex;
}
void Paralelogram::setVertex(b2Vec2 * vertex) {
	for (size_t i = 0; i < 4; i++) {
		this->addB2DPoint(vertex[i].x, vertex[i].y);
	}
}
Paralelogram::~Paralelogram() {
	// TODO Auto-generated destructor stub
}
