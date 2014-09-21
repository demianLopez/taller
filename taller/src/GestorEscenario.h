/*
 * GestorEscenario.h
 *
 *  Created on: 17/9/2014
 *      Author: FireHorse
 */

#ifndef GESTORESCENARIO_H_
#define GESTORESCENARIO_H_

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
	int lados;
	int posX ;
	int posY ;
	float radio;
	string color;
	float rot;
	float masa;
	bool estatico;
};

class GestorEscenario {
public:
	GestorEscenario();
	virtual ~GestorEscenario();
	escenario* getEscenario();
	void configurarEscenerio(int altopx,int anchopx,int altoun,int anchoun,string imagen_fondo,int personajeX,int personajeY);
	void agregarObjeto(string tipo,int lados,int posX,int posY,float radio,string color,float rot, float masa, bool estado);
private:
	escenario * elEscenario;
	vector<objeto> * objetos;

};

#endif /* GESTORESCENARIO_H_ */
