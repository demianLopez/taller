/*
 * LectorJsonTest.cpp
 *
 *  Created on: 17/9/2014
 *      Author: FireHorse
 */

#include "LectorJsonTest.h"

const char* ESCENARIO_DEFECTO = "Resources/escenario.json";

LectorJsonTest::LectorJsonTest() {
	// TODO Auto-generated constructor stub

}

LectorJsonTest::~LectorJsonTest() {
	// TODO Auto-generated destructor stub
}

void LectorJsonTest::imprimirXConsola(){
	Value raiz;
	Reader lector;
	bool parseExitoso = lector.parse(ESCENARIO_DEFECTO,raiz,false);
	if(!parseExitoso){
		cout << "Fallo el parseo del archivo" << endl;
	}
	Value escenario = raiz.get("escenario", "No existe");
	if (escenario.isNull()){
		cout<< "No se encontro Escenario" << endl;
	}
	else{
		cout << "Descripcion escenario:"<< endl;
		Value dato = escenario["altopx"];
		cout<< "altopx = " << dato.asInt() << endl;
		dato = escenario["anchopx"];
		cout<< "anchopx = " << dato.asInt() << endl;
		dato = escenario["altoun"];
		cout<< "altoun = " << dato.asInt() << endl;
		dato = escenario["anchoun"];
		cout<< "anchoun = " << dato.asInt() << endl;
		cout << "Descripcion personaje:"<< endl;
		Value personaje = escenario["personaje"];
		dato = personaje["x"];
		cout<< "x = " << dato.asInt() << endl;
		dato = personaje["x"];
		cout<< "x = " << dato.asInt() << endl;
	}
}

//El main para probarlo:
/*
int main(int argc, char* args[]){
	LectorJsonTest* lector = new LectorJsonTest("dfadf");

	lector->imprimirXConsola();
	delete lector;
	return 0;
}
 */
