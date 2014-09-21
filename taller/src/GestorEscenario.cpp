/*
 * GestorEscenario.cpp
 *
 *  Created on: 17/9/2014
 *      Author: FireHorse
 */

#include "GestorEscenario.h"

GestorEscenario::GestorEscenario() {
	// TODO Auto-generated constructor stub

}

GestorEscenario::~GestorEscenario() {
	// TODO Auto-generated destructor stub
}

void GestorEscenario::configurarEscenerio(int altopx,int anchopx,int altoun,int anchoun,string imagen_fondo,int personajeX,int personajeY){
	this->elEscenario.altopx = altopx;
	this->elEscenario.anchopx = anchopx;
	this->elEscenario.altoun =  altoun;
	this->elEscenario.anchoun = anchoun;
	this->elEscenario.imagen_fondo = imagen_fondo;
	this->elEscenario.personajeX = personajeX;
	this->elEscenario.personajeY = personajeY;
}

void GestorEscenario::imprimirXConsola(){
	cout << "Descripcion escenario:"<< endl;
	cout<< "altopx = " << elEscenario.altopx << endl;
	cout<< "anchopx = " << elEscenario.anchopx << endl;
	cout<< "altoun = " << elEscenario.altoun << endl;
	cout<< "anchoun = " << elEscenario.anchoun << endl;
	cout<< "Dir Image: " << elEscenario.imagen_fondo << endl;
	cout << "Descripcion personaje:"<< endl;
	cout<< "x = " << elEscenario.personajeX << endl;
	cout<< "y = " << elEscenario.personajeY << endl;
}

