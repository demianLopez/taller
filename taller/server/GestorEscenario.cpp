/*
 * GestorEscenario.cpp
 *
 *  Created on: 17/9/2014
 *      Author: FireHorse
 */

#include "GestorEscenario.h"
#include <Box2D/Box2D.h>
#include "polygons/PolygonFactory.h"
#include "../common/Logger.h"

GestorEscenario::GestorEscenario() {

}

GestorEscenario::~GestorEscenario() {
}

escenario* GestorEscenario::getEscenario() {
	return &elEscenario;
}

void GestorEscenario::configurarEscenerio(int altopx, int anchopx, int altoun,
		int anchoun, string imagen_fondo, int personajeX, int personajeY,
		int cantidadJugadores, string nombreMapa, string sigNivel, int minJug
		, double * posiciones) {
	this->elEscenario.altopx = altopx;
	this->elEscenario.anchopx = anchopx;
	this->elEscenario.altoun = altoun;
	this->elEscenario.anchoun = anchoun;
	this->elEscenario.imagen_fondo = imagen_fondo;
	this->elEscenario.personajeX = personajeX;
	this->elEscenario.personajeY = personajeY;
	this->elEscenario.cantidadJugadores = cantidadJugadores;
	this->elEscenario.nombreMapa = nombreMapa;
	this->elEscenario.sigNivel = sigNivel;
	this->elEscenario.minJug = minJug;
	this->elEscenario.pos = posiciones;
}

escenario GestorEscenario::datos() {
	return elEscenario;
}

void GestorEscenario::agregarObjeto(string tipo, double posX, double posY,
		string color, double rot, double masa, double escala, bool estado,
		double alto, double ancho, int lados, double radio, double baseParal,
		double angulo, double base_superior, double base_inferior) {
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
	nuevoObjeto.base_superior = base_superior;
	nuevoObjeto.base_inferior = base_inferior;
	this->objetos.push_back(nuevoObjeto);
}

void GestorEscenario::setActual(const char* actual){
	this->escenarioActual = (char*)actual;
}

char * GestorEscenario::getActual(){
	return escenarioActual	;
}

void GestorEscenario::agregarEnemigo(int tipo,double posx,double posy){
	enemy nuevoEnemigo;
	nuevoEnemigo.tipo = tipo;
	nuevoEnemigo.posx = posx;
	nuevoEnemigo.posy = posy;
	this-> enemigos.push_back(nuevoEnemigo);
}


void GestorEscenario::imprimirXConsola() {
	cout << "Descripcion escenario:" << endl;
	cout << "altopx = " << elEscenario.altopx << endl;
	cout << "anchopx = " << elEscenario.anchopx << endl;
	cout << "altoun = " << elEscenario.altoun << endl;
	cout << "anchoun = " << elEscenario.anchoun << endl;
	cout << "Dir Image: " << elEscenario.imagen_fondo << endl;
	cout << "Descripcion personaje:" << endl;
	cout << "x = " << elEscenario.personajeX << endl;
	cout << "y = " << elEscenario.personajeY << endl;
	this->obtenerObjetos();
}

void GestorEscenario::obtenerObjetos() {
	for (unsigned int i = 0; i < objetos.size(); i++) {
		string tipo = objetos[i].tipo;
		if (tipo == "rect") {
			this->colocarRect(objetos[i]);
		} else if (tipo == "poli") {
			this->colocarPoli(objetos[i]);
		} else if (tipo == "circ") {
			this->colocarCirc(objetos[i]);
		} else if (tipo == "paral") {
			this->colocarParal(objetos[i]);
		} else if (tipo == "trap") {
			this->colocarTrap(objetos[i]);
		} else {
			return;
		}
	}
}

void imprimirRGB(objeto figura) {
	cout << "Color en RGB:" << endl;
	cout << "Rojo:" << figura.colRGB.red << endl;
	cout << "Verde:" << figura.colRGB.green << endl;
	cout << "Azul:" << figura.colRGB.blue << endl;
}

World * GestorEscenario::obtenerMundo() {
	world = new World(new b2Vec2(0, -20));
	world->setUnits(elEscenario.anchoun, elEscenario.altoun);

	world->setMapData(new string(elEscenario.nombreMapa),
			elEscenario.cantidadJugadores);
	b2Vec2 SDLCharPos = b2Vec2(elEscenario.personajeX, elEscenario.personajeY);

	world->setNextLevelName((char *)elEscenario.sigNivel.c_str());
	world->setCurrentLevelName(escenarioActual);
	world->setMinPlayers(elEscenario.minJug);

	world->addPlayerPos(elEscenario.pos[0], elEscenario.pos[1]);
	world->addPlayerPos(elEscenario.pos[2], elEscenario.pos[3]);
	world->addPlayerPos(elEscenario.pos[4], elEscenario.pos[5]);
	world->addPlayerPos(elEscenario.pos[6], elEscenario.pos[7]);

	delete[] elEscenario.pos;

	for(auto enemigo : enemigos){
		Enemigo * enemy = new Enemigo(NULL);
		enemy->colocar(enemigo.tipo,enemigo.posx,enemigo.posy);

		world->addEnemy(enemy);
	}

	for (auto objeto : objetos) {

		string tipo = objeto.tipo;
		Polygon * nuevoPoligono;

		if (tipo == "rect") {
			nuevoPoligono = this->colocarRect(objeto);
		} else if (tipo == "poli") {
			nuevoPoligono = this->colocarPoli(objeto);
		} else if (tipo == "circ") {
			nuevoPoligono = this->colocarCirc(objeto);
		} else if (tipo == "paral") {
			nuevoPoligono = this->colocarParal(objeto);
		} else if (tipo == "trap") {
			nuevoPoligono = this->colocarTrap(objeto);
		}

		bool todoOk = true;
		for (auto * alreadyAddedPolygon : world->getPolygonList()) {
			b2Shape * shapeNew =
					(b2Shape*) nuevoPoligono->getBody()->GetFixtureList()->GetShape();
			b2Shape * shapeAlreadyAdded =
					(b2Shape*) alreadyAddedPolygon->getBody()->GetFixtureList()->GetShape();
			if (!bothStatic(alreadyAddedPolygon, nuevoPoligono)
					&& b2TestOverlap(shapeNew, 0, shapeAlreadyAdded, 0,
							nuevoPoligono->getBody()->GetTransform(),
							alreadyAddedPolygon->getBody()->GetTransform())) {
				todoOk = false;
			}
		}
		if (nuevoPoligono && todoOk) {
			world->addPolygon(nuevoPoligono);
		} else {
			world->getBox2DWorld()->DestroyBody(nuevoPoligono->getBody());
			delete nuevoPoligono;
			Logger::customLog("GestorEscenario.cpp", Logger::WARNING,
					"Objetos superpuestos, se elimina el segundo");
		}

	}

	return world;

}

Polygon * GestorEscenario::colocarRect(objeto figura) {
	if (figura.estatico) {
		return PolygonFactory::get_static_rectangle(figura.alto, figura.ancho,
				figura.posX, figura.posY, figura.masa, figura.rot / 57, world);
	}
	return PolygonFactory::get_dynamic_rectangle(figura.alto, figura.ancho,
			figura.posX, figura.posY, figura.masa, figura.rot / 57, world);
	/*cout << "\n Datos Rectangulo" << endl;
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
	 */
}

Polygon * GestorEscenario::colocarPoli(objeto figura) {
	if (figura.estatico) {
		return PolygonFactory::get_static_regular_polygon(figura.lados,
				figura.escala, figura.posX, figura.posY, figura.masa,
				figura.rot / 57, world);
	}
	return PolygonFactory::get_dynamic_regular_polygon(figura.lados,
			figura.escala, figura.posX, figura.posY, figura.masa,
			figura.rot / 57, world);

	/*
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
	 */
}

Polygon * GestorEscenario::colocarCirc(objeto figura) {
	if (figura.estatico) {
		return PolygonFactory::get_static_circle(figura.radio * 2, figura.posX,
				figura.posY, figura.masa, figura.rot / 57, world);
	}
	return PolygonFactory::get_dynamic_circle(figura.radio * 2, figura.posX,
			figura.posY, figura.masa, figura.rot / 57, world);
	/*
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
	 */
}

Polygon * GestorEscenario::colocarParal(objeto figura) {
	if (figura.estatico) {
		return PolygonFactory::get_static_paralelogram(figura.baseParal,
				figura.alto, figura.angulo, figura.posX, figura.posY,
				figura.masa, figura.rot / 57, world);
	}
	return PolygonFactory::get_dynamic_paralelogram(figura.baseParal,
			figura.alto, figura.angulo, figura.posX, figura.posY, figura.masa,
			figura.rot / 57, world);
	/*
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
	 */
}

Polygon * GestorEscenario::colocarTrap(objeto figura) {
	if (figura.estatico) {
		return PolygonFactory::get_static_trapezoid(figura.alto,
				figura.base_inferior, figura.base_superior, figura.angulo,
				figura.posX, figura.posY, figura.masa, figura.rot / 57, world);
	}
	return PolygonFactory::get_dynamic_trapezoid(figura.alto,
			figura.base_inferior, figura.base_superior, figura.angulo,
			figura.posX, figura.posY, figura.masa, figura.rot / 57, world);
	/*
	 cout << "\n Datos Trapecio" << endl;
	 cout <<"PosX: " << figura.posX << endl;
	 cout <<"PosY: " << figura.posY << endl;
	 cout <<"Color: " << figura.color << endl;
	 imprimirRGB(figura);
	 cout <<"Rotacion: " << figura.rot << endl;
	 cout <<"Masa: " << figura.masa << endl;
	 cout <<"Escala: " << figura.escala << endl;
	 cout <<"Estatico: " << figura.estatico << endl;

	 cout << "Base Mayor: " << figura.base_superior << endl;
	 cout << "Base Menor: " << figura.base_inferior << endl;
	 cout << "Angulo: " << figura.angulo << endl;
	 */
}

int GestorEscenario::calcularColor(char col1, char col2) {
	int color = 0;
	if ((int(col2) >= 48) && (int(col2) <= 57))
		color = color + (int(col2) - 48);
	else
		color = color + (int(col2) - 55);
	if ((int(col1) >= 48) && (int(col1) <= 57))
		color = color + ((int(col1) - 48) * 16);
	else
		color = color + ((int(col1) - 55) * 16);
	return color;
}

rgb GestorEscenario::obtenerRGB(string color) {
	rgb colores;
	colores.red = this->calcularColor(color[1], color[2]);
	colores.green = this->calcularColor(color[3], color[4]);
	colores.blue = this->calcularColor(color[5], color[6]);
	return colores;
}

bool GestorEscenario::bothStatic(Polygon * aPolygon, Polygon * anotherPolygon) {
	return aPolygon->isStatic() && anotherPolygon->isStatic();
}

