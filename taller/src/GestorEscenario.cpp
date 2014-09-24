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
	nuevoObjeto.colRGB = this->obtenerRGB(color);
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
	this->obtenerObjetos();
}

void GestorEscenario::obtenerObjetos(){
	for (unsigned int i = 0 ; i < objetos.size() ; i++){
		string tipo = objetos[i].tipo;
		if (tipo == "rect"){
			this->colocarRect(objetos[i]);
		}else if (tipo == "poli"){
			this->colocarPoli(objetos[i]);
		}else if (tipo == "circ"){
			this->colocarCirc(objetos[i]);
		}else if (tipo == "paral"){
			this->colocarParal(objetos[i]);
		}else if (tipo == "trap"){
			this->colocarTrap(objetos[i]);
		}else{
			return;
		}
	}
}

void imprimirRGB(objeto figura){
	cout << "Color en RGB:" << endl;
	cout << "Rojo:" << figura.colRGB.red << endl;
	cout << "Verde:" << figura.colRGB.green << endl;
	cout << "Azul:" << figura.colRGB.blue << endl;
}

void GestorEscenario::colocarRect(objeto figura){
	cout << "\n Datos Rectangulo" << endl;
	cout <<"PosX: " << figura.posX << endl;
	cout <<"PosY: " << figura.posY << endl;
	cout <<"Color: " << figura.color << endl;
	imprimirRGB(figura);
	cout <<"Rotacion: " << figura.rot << endl;
	cout <<"Masa: " << figura.masa << endl;
	cout <<"Escala: " << figura.escala << endl;
	cout <<"Estatico: " << figura.estatico << endl;

	cout <<"Alto: " << figura.alto << endl;
	cout <<"Ancho: " << figura.ancho << endl;
}

void GestorEscenario::colocarPoli(objeto figura){
	cout << "\n Datos Poligono" << endl;
	cout <<"PosX: " << figura.posX << endl;
	cout <<"PosY: " << figura.posY << endl;
	cout <<"Color: " << figura.color << endl;
	imprimirRGB(figura);
	cout <<"Rotacion: " << figura.rot << endl;
	cout <<"Masa: " << figura.masa << endl;
	cout <<"Escala: " << figura.escala << endl;
	cout <<"Estatico: " << figura.estatico << endl;

	cout << "Lados: " << figura.lados << endl;
}

void GestorEscenario::colocarCirc(objeto figura){
	cout << "\n Datos Circulo" << endl;
	cout <<"PosX: " << figura.posX << endl;
	cout <<"PosY: " << figura.posY << endl;
	cout <<"Color: " << figura.color << endl;
	imprimirRGB(figura);
	cout <<"Rotacion: " << figura.rot << endl;
	cout <<"Masa: " << figura.masa << endl;
	cout <<"Escala: " << figura.escala << endl;
	cout <<"Estatico: " << figura.estatico << endl;

	cout << "Radio: " << figura.radio << endl;
}

void GestorEscenario::colocarParal(objeto figura){
	cout << "\n Datos Paralelogramo" << endl;
	cout <<"PosX: " << figura.posX << endl;
	cout <<"PosY: " << figura.posY << endl;
	cout <<"Color: " << figura.color << endl;
	imprimirRGB(figura);
	cout <<"Rotacion: " << figura.rot << endl;
	cout <<"Masa: " << figura.masa << endl;
	cout <<"Escala: " << figura.escala << endl;
	cout <<"Estatico: " << figura.estatico << endl;

	cout << "Base: " << figura.baseParal << endl;
	cout << "Angulo: " << figura.angulo << endl;
	cout << "Alto: " << figura.alto << endl;
}

void GestorEscenario::colocarTrap(objeto figura){
	cout << "\n Datos Trapecio" << endl;
	cout <<"PosX: " << figura.posX << endl;
	cout <<"PosY: " << figura.posY << endl;
	cout <<"Color: " << figura.color << endl;
	imprimirRGB(figura);
	cout <<"Rotacion: " << figura.rot << endl;
	cout <<"Masa: " << figura.masa << endl;
	cout <<"Escala: " << figura.escala << endl;
	cout <<"Estatico: " << figura.estatico << endl;

	cout << "Base Mayor: " << figura.base_mayor << endl;
	cout << "Base Menor: " << figura.base_menor << endl;
	cout << "Angulo: " << figura.angulo << endl;
}

int GestorEscenario::calcularColor(char col1, char col2){
	int color = 0;
	if((int(col2) >= 48) && (int(col2) <= 57))
		color = color + (int(col2)-48);
	else
		color = color + (int(col2)-55);
	if ((int(col1) >= 48) && (int(col1) <= 57))
		color = color + ((int(col1)-48)*16);
	else
		color = color + ((int(col1)-55)*16);
	return color;
}

rgb GestorEscenario::obtenerRGB(string color){
	rgb colores;
	colores.red = this->calcularColor(color[1],color[2]);
	colores.green = this->calcularColor(color[3],color[4]);
	colores.blue = this->calcularColor(color[5],color[6]);
	return colores;
}

