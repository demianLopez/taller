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

Model_polygon::Model_polygon(int body_type, double density) {
	if (body_type == STATIC) {
		this->body_type = b2_staticBody;
	} else { //Por defecto es dinamico (body_type == DYNAMIC)
		this->body_type = b2_dynamicBody;
	}

	this->body = NULL;
	this->density = density;
}

Model_polygon::~Model_polygon() {
	// TODO Auto-generated destructor stub
}

void Model_polygon::rotate(double angle) {

}

void Model_polygon::move(double x_units, double y_units) {
}

void Model_polygon::set_velocity(double x_units, double y_units) {
	b2Vec2 velocity(x_units, y_units);
	this->body->SetLinearVelocity(velocity);
}

void Model_polygon::set_angular_velocity(double angular_velocity) {
	this->body->SetAngularVelocity(angular_velocity);
}

void Model_polygon::apply_force(double x_units, double y_units) {
	b2Vec2 force(x_units, y_units);
	this->body->ApplyForceToCenter()
}

void Model_polygon::apply_instant_force(double x_units, double y_units) {
	b2Vec2 force(x_units, y_units);

}

void Model_polygon::create_body(b2BodyDef* body_definition,
		b2FixtureDef* body_fixture, b2World& world) {
	this->body = world.CreateBody(body_definition);
	this->body->CreateFixture(body_fixture);

	this->body->SetSleepingAllowed(true); //Los objetos tienen que poder dormir para no consumir recursos de mas
}
