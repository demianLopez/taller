/**
 Trapezoid.cpp

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
#include "Trapezoid.h"
#include "../../game/engine/GameElements.h"
#include "../../game/engine/SdlGfx/SDL2_gfxPrimitives.h"

b2Vec2 * Trapezoid::define_vertex(double angle, double height, double base,
		double top) {
	/* if (base>top)
	 {
	 if (!(angle <= 3.14/2 )) return NULL;
	 }

	 else
	 {
	 if (!(angle >= 3.14/2 )) return NULL;
	 }
	 */

	double a = top;
	double b = base;
	double c = height / sin(angle);
	double secondTriangleBase = base - top - height / tan(angle);
	double d = sqrt(pow(secondTriangleBase, 2) + pow(height, 2));

	double centerX = (b / 2
			+ ((2 * a + b) * (c * c - d * d)) / (6 * (b * b - a * a)));
	double centerY = height * 0.5;
	//((2*a + b) * sqrt((a-b+c+d)*(a-b-c+d)*(a-b+c+d)*(-a+b+c+d))) / (6 * (b*b-a*a));

	double ady = height / tan(angle);

	b2Vec2 * vertex = new b2Vec2[4];

	vertex[0].Set(-centerX, -centerY);

	vertex[1].Set(ady - centerX, height - centerY);
	ady += top;
	vertex[2].Set(ady - centerX, height - centerY);
	vertex[3].Set(base - centerX, -centerY);

	return vertex;
}

Trapezoid::Trapezoid(double height, double base, double top, double angle,
		double posX, double posY, double density, double rotation,
		int body_type, World * world) :
		Polygon(body_type) {

	b2Vec2* vertex = this->define_vertex(angle, height, base, top);

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

/*
 void Trapezoid::render(Graphics *g){
 SDL_Rect imageData = {20, 20, 200, 200};
 SDL_RenderCopy(GameElements::gRenderer, text, NULL, &imageData);

 }
 */
void Trapezoid::setVertex(b2Vec2 * vertex) {
	for (size_t i = 0; i < 4; i++) {
		this->addB2DPoint(vertex[i].x, vertex[i].y);
	}
}

Trapezoid::~Trapezoid() {

}

