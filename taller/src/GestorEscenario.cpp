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

escenario GestorEscenario::datos(){
	return elEscenario;
}

void GestorEscenario::agregarObjeto(string tipo,double posX,double posY,string color,double rot,double masa,double escala,bool estado,
			double alto,double ancho,
			int lados,
			double radio,
			double baseParal,double angulo,
			double base_mayor,double base_menor){
	objeto nuevoObjeto;
	nuevoObjeto.tipo = tipo;
	nuevoObjeto.posX = posX;
	nuevoObjeto.posY = posY;
	nuevoObjeto.color = color;
	nuevoObjeto.rot = rot;
	nuevoObjeto.masa = masa;
	nuevoObjeto.escala = escala;
	nuevoObjeto.estatico = estado;
	nuevoObjeto.alto = alto;
	nuevoObjeto.ancho = ancho;
	nuevoObjeto.lados = lados;
	nuevoObjeto.radio = radio;
	nuevoObjeto.baseParal = baseParal;
	nuevoObjeto.angulo = angulo;
	nuevoObjeto.base_mayor = base_mayor;
	nuevoObjeto.base_menor = base_menor;
	this->objetos.push_back(nuevoObjeto);
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

