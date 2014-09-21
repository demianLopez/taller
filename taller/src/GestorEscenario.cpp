/*
 * GestorEscenario.cpp
 *
 *  Created on: 17/9/2014
 *      Author: FireHorse
 */

#include "GestorEscenario.h"

GestorEscenario::GestorEscenario() {
	this->elEscenario = NULL;
	objetos = new vector<objeto>;
	// TODO Auto-generated constructor stub

}

GestorEscenario::~GestorEscenario() {
	this->elEscenario = NULL;
	this->objetos = NULL;
	// TODO Auto-generated destructor stub
}

void GestorEscenario::configurarEscenerio(int altopx,int anchopx,int altoun,int anchoun,string imagen_fondo,int personajeX,int personajeY){
	this->elEscenario->altopx = altopx;
	this->elEscenario->anchopx = anchopx;
	this->elEscenario->altoun =  altoun;
	this->elEscenario->anchoun = anchoun;
	this->elEscenario->imagen_fondo = imagen_fondo;
	this->elEscenario->personajeX = personajeX;
	this->elEscenario->personajeY = personajeY;
}


