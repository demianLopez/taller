/*
 * LectorJson.h
 *
 *  Created on: 18/9/2014
 *      Author: FireHorse
 */

#ifndef LECTORJSON_H_
#define LECTORJSON_H_

#include <iostream>
#include "json/json.h"
#include <fstream>
#include "LogManager.h"
#include <string.h>
#include <stdlib.h>
#include "GestorEscenario.h"

using namespace std;
using namespace Json;

class LectorJson {
private:
	int validarInt(string miembro, Value raiz, int valorDefecto,
			string codigoObjeto);
	double validarDouble(string miembro, Value raiz, double valorDefecto,
			string codigoObjeto);
	string validarColor(string miembro, Value raiz, string valorDefecto,
			string codigoObjeto);
	string validarNombreMapa(string miembro, Value raiz, string valorDefecto,
			string codigoObjeto);
	string validarImagen(string miembro, Value raiz, string valorDefecto,
			string codigoObjeto);
	bool validarBool(string miembro, Value raiz, bool valorDefecto,
			string codigoObjeto);
	int validarComunes(Value objeto, double *posx, double *posy, double *rot,
			double *masa, string *color, double *escala, bool *estado,
			string codigoObjeto);
	void obtenerEscenario(Value raiz);
	void obtenerObjetos(Value raiz);
	void crearObjeto(Value objeto);
	void armarRectangulo(Value objeto);
	void armarPoligon(Value objeto);
	void armarCirculo(Value objeto);
	void armarParalelogramo(Value objeto);
	void armarTrapecio(Value objeto);

	LogManager* logger;
	GestorEscenario * elEscenario;
public:
	void cargarEscenario(const char* rutaArchivo);
	GestorEscenario * obtenerGestorEscenario();

	LectorJson();
	virtual ~LectorJson();
};

#endif /* LECTORJSON_H_ */
