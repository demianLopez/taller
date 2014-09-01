#include "VectorXY.h"

// Se crea por defecto en (0, 0)
VectorXY::VectorXY(float x, float y) {
	this->x = x;
	this->y = y;
}

// Se crea en la misma posicion que vector.
VectorXY::VectorXY(VectorXY *vector){
	this->x = vector->x;
	this->y = vector->y;
}

// Setea valores de x e y.
void VectorXY::set(float x, float y){
	this->x = x;
	this->y = y;
}

// Aumenta valores en x e y.
void VectorXY::aumentarEn(float x, float y){
	this->x += x;
	this->y += y;
}

void VectorXY::aumentarEn(VectorXY vector){
	this->x += vector.x;
	this->y += vector.y;
}
