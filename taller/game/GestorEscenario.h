/*
 * GestorEscenario.h
 *
 *  Created on: 17/9/2014
 *      Author: FireHorse
 */

#ifndef GESTORESCENARIO_H_
#define GESTORESCENARIO_H_

#include <iostream>
#include <string>
#include <vector>
#include "polygons/Polygon.h"
#include "World.h"

using namespace std;

struct escenario{
	int altopx;
	int anchopx;
	int altoun;
	int anchoun;
	string imagen_fondo;
	int personajeX;
	int personajeY;
};

struct rgb{
	int red;
	int green;
	int blue;
};

struct objeto{
	string tipo;
	int lados = 0;
	double alto = 0;
	double ancho = 0;
	double posX = 0 ;
	double posY = 0 ;
	double baseParal = 0;
	double base_inferior = 0;
	double base_superior = 0;
	double angulo = 0;
	double radio = 0;
	string color = "#FF00FF";
	rgb colRGB;
	double rot = 0;
	double masa = 0;
	double escala = 0;
	bool estatico = true;
};

class GestorEscenario {
public:
	GestorEscenario();
	virtual ~GestorEscenario();
	escenario* getEscenario();
	void imprimirXConsola();
	escenario datos();
	void configurarEscenerio(int altopx,int anchopx,int altoun,int anchoun,string imagen_fondo,int personajeX,int personajeY);
	void agregarObjeto(string tipo,double posX,double posY,string color,double rot,double masa,double escala,bool estado,
			double alto,double ancho,
			int lados,
			double radio,
			double baseParal,double angulo,
			double base_superior,double base_inferior);
	void obtenerObjetos();
	Polygon * colocarRect(objeto figura);
	Polygon * colocarPoli(objeto figura);
	Polygon * colocarCirc(objeto figura);
	Polygon * colocarParal(objeto figura);
	Polygon * colocarTrap(objeto figura);
	rgb obtenerRGB(string color);
	int calcularColor(char col1, char col2);

	World * obtenerMundo();
private:
	escenario elEscenario;
	vector<objeto> objetos;
	World * world;

	bool bothStatic(Polygon * aPolygon, Polygon * anotherPolygon);

};

#endif /* GESTORESCENARIO_H_ */
