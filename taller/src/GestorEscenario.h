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

struct objeto{
	string tipo;
	int lados = 0;
	double alto = 0;
	double ancho = 0;
	double posX = 0 ;
	double posY = 0 ;
	double baseParal = 0;
	double base_menor = 0;
	double base_mayor = 0;
	double angulo = 0;
	double radio = 0;
	string color = "#FF00FF";
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
			double base_mayor,double base_menor);
private:
	escenario elEscenario;
	vector<objeto> objetos;

};

#endif /* GESTORESCENARIO_H_ */
