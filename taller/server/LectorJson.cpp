/*
 * LectorJson.cpp
 *
 *  Created on: 18/9/2014
 *      Author: FireHorse
 */

#include "LectorJson.h"

//Escenario por defecto
const char* ESCENARIO_X_DEFECTO = "Resources/escenario.json";

//Valores por defecto escenario
const int ALTOPX_D = 720;
const int ANCHOPX_D = 1024;
const int ALTOPX_MIN_D = 50;
const int ANCHOPX_MIN_D = 50;
const int ALTOUN_D = 100;
const int ANCHOUN_D = 50;
const string IMAGEN_FONDO_D = "Resources/font1.png";
const int CANTIDADJUGADORES_D = 4;
const int MIN_JUG = 1;

//Valores por defecto personaje
const int POSX_D = 100;
const int POSY_D = 100;

//Valores por defecto objeto
const double POS_OBJ_INV = -1.111;
const double ANCHO_OBJ_D = 1.0;
const double ALTO_OBJ_D = 1.0;
const int LADOS_OBJ_D = 3;
const double RADIO_OBJ_D = 1.0;
const double BASE_OBJ_D = 2.0;
const string COLOR_OBJ_D = "#00FF00";
const double ROT_OBJ_D = 0;
const double MASA_OBJ_D = 1.0;
const double ESCALA_OBJ_D = 1.0;
const double ANGULO_OBJ_D = 45.0;
const double BASE_SUPERIOR_OBJ_D = 4.0;
const double BASE_INFERIOR_OBJ_D = 2.0;
const bool EST_OBJ_D = true;


//Tipo de problemas
const int ERROR = 1;
const int WARNING = 2;
const int FATAL = 3;
const int INVALIDO = -1;
const int OK = 0;

LectorJson::LectorJson() {
	logger = new LogManager();
	elEscenario = new GestorEscenario();
}

LectorJson::~LectorJson() {
	delete logger;
	delete elEscenario;
}

int LectorJson::validarInt(string miembro, Value raiz, int valorDefecto,
		string codigoObjeto) {
	Value clave = raiz[miembro];
	if (clave.isNull()) {
		//logger->reportarProblema(raiz.asCString(), WARNING);
		logger->reportarProblema(
				"No existe el miembro '" + miembro + "' en objeto: "
						+ codigoObjeto + "Cargo entero por defecto.", WARNING);
		return valorDefecto;
	}
	if (!clave.isInt()) {
		logger->reportarProblema(
				"El miembro '" + miembro + "' no es entero en objeto: "
						+ codigoObjeto + ". Cargo entero por defecto.",
				WARNING);
		return valorDefecto;
	}
	return (clave.asInt());
}

double LectorJson::validarDouble(string miembro, Value raiz,
		double valorDefecto, string codigoObjeto) {
	Value clave = raiz[miembro];
	if (clave.isNull()) {
		logger->reportarProblema(
				"No existe el miembro '" + miembro + "' en objeto: "
						+ codigoObjeto + ". Cargo double por defecto.",
				WARNING);
		return valorDefecto;
	}
	if (!clave.isDouble()) {
		if (clave.isInt())
			return (clave.asDouble());
		else {
			logger->reportarProblema(
					"El miembro '" + miembro
							+ "' no es un valor valido en objeto: "
							+ codigoObjeto + ". Cargo double por defecto.",
					WARNING);
			return valorDefecto;
		}
	}
	return (clave.asDouble());
}

bool LectorJson::validarBool(string miembro, Value raiz, bool valorDefecto,
		string codigoObjeto) {
	Value boolean = raiz[miembro];
	if (boolean.isNull()) {
		logger->reportarProblema(
				"No existe el miembro '" + miembro + "' en objeto: "
						+ codigoObjeto + ". Cargo booleano por defecto.",
				WARNING);
		return valorDefecto;
	}
	if (!boolean.isBool()) {
		logger->reportarProblema(
				"El miembro '" + miembro + "' no es bool en objeto: "
						+ codigoObjeto + ". Cargo booleano por defecto.",
				WARNING);
		return valorDefecto;
	}
	return (boolean.asBool());
}

GestorEscenario * LectorJson::obtenerGestorEscenario() {
	return this->elEscenario;
}

string LectorJson::validarColor(string miembro, Value raiz, string valorDefecto,
		string codigoObjeto) {
	Value color = raiz[miembro];
	if (color.isNull()) {
		logger->reportarProblema(
				"No existe el miembro '" + miembro + "' en objeto: "
						+ codigoObjeto + ". Cargo color por defecto.", WARNING);
		return valorDefecto;
	}
	if (!color.isString()) {
		logger->reportarProblema(
				"Formato de color invalido en " + raiz["tipo"].asString() + //para obtener color debe exitir tipo
						". Cargo color por defecto.", WARNING);
		return valorDefecto;
	}
	if (!((color.asString().size() == 7) && (color.asString()[0] == '#'))) {
		logger->reportarProblema(
				"Formato de color invalido en " + raiz["tipo"].asString() + //para obtener color debe exitir tipo
						". Cargo color por defecto.", WARNING);
		return valorDefecto;
	}
	string col = color.asString();
	for (unsigned int i = 1; i < color.asString().size(); i++) {
		if (!((int(col[i]) >= 48 && int(col[i]) <= 57)
				|| (int(col[i]) >= 65 && int(col[i]) <= 70))) {
			string e1 = "Valor<";
			e1 += col[i];
			e1 += "> para definir color no es valido. Se coloca por defecto F";
			logger->reportarProblema(e1, WARNING);
			col[i] = 'F';
		}
	}
	return col;
}

string LectorJson::validarNombreMapa(string miembro, Value raiz,
		string valorDefecto, string codigoObjeto) {
	Value texto = raiz[miembro];
	if (texto.isNull()) {
		logger->reportarProblema(
				"No existe el miembro '" + miembro + "' en objeto: "
						+ codigoObjeto + ". Cargo texto por defecto.", WARNING);
		return valorDefecto;
	}
	if (!texto.isString()) {
		logger->reportarProblema(
				"Formato de texto invalido. Carga texto por defecto", WARNING);
		return valorDefecto;
	}

	return (texto.asString());
}

string LectorJson::validarImagen(string miembro, Value raiz,
		string valorDefecto, string codigoObjeto) {
	Value imagen = raiz[miembro];
	if (imagen.isNull()) {
		logger->reportarProblema(
				"No existe el miembro '" + miembro + "' en objeto: "
						+ codigoObjeto + ". Cargo imagen por defecto.",
				WARNING);
		return valorDefecto;
	}
	if (!imagen.isString()) {
		logger->reportarProblema(
				"Formato de imagen invalido. Carga imgen por defecto", WARNING);
		return valorDefecto;
	}
	ifstream imagenFondo(imagen.asString(), std::ifstream::binary);
	if (!imagenFondo.good()) {
		if (imagen.asString() == valorDefecto) {
			logger->reportarProblema(
					"No existe imagen por defecto, debe crear una.", FATAL);
			exit(0);
		} else {
			logger->reportarProblema(
					"La ruta de la imagen de fondo no existe. Carga imagen por defecto.",
					WARNING);
			return valorDefecto;
		}
	}
	return (imagen.asString());
}

void LectorJson::obtenerEscenario(Value raiz) {
	Value escenario = raiz["escenario"];
	if (escenario.isNull()) {
		logger->reportarProblema(
				"No se encontro la clave 'escenario'. Carga Escenario por defecto.",
				ERROR);
		this->cargarEscenario(ESCENARIO_X_DEFECTO);
		return;
	} else {
		int altopx = validarInt("altopx", escenario, ALTOPX_D, "escenario");
		/*
		if (altopx < ALTOPX_MIN_D) {
			logger->reportarProblema(
					"No se permite altura de ventana menor a 50. Se carga tamano por defecto.",
					WARNING);
			altopx = ALTOPX_MIN_D;
		}
		*/
		int anchopx = validarInt("anchopx", escenario, ALTOPX_D, "escenario");
		/*
		if (anchopx < ANCHOPX_MIN_D) {
			logger->reportarProblema(
					"No se permite ancho de ventana menor a 50. Se carga tamano por defecto.",
					WARNING);
			altopx = ANCHOPX_MIN_D;
		}
		*/
		int altoun = validarInt("altoun", escenario, ALTOPX_D, "escenario");
		int anchoun = validarInt("anchoun", escenario, ALTOPX_D, "escenario");
		string imagen = validarImagen("imagen_fondo", escenario, IMAGEN_FONDO_D,
				"escenario");
		Value personaje = escenario["personaje"];

		int x;

		int y;

		if (personaje.isNull()) {
			logger->reportarProblema(
					"No se encontro clave 'personaje'. Carga personaje por defecto.",
					WARNING);
			x = POSX_D;
			y = POSY_D;
		} else {
			x = validarDouble("x", personaje, POSX_D, "personaje");
			y = validarDouble("y", personaje, POSY_D, "personaje");
		}
		//obtengo las posiciones de los jugadores
		double	x_1 = validarDouble("x1", personaje, POSX_D, "personaje");
		double	y_1 = validarDouble("y1", personaje, POSY_D, "personaje");
		double	x_2 = validarDouble("x2", personaje, POSX_D, "personaje");
		double	y_2 = validarDouble("y2", personaje, POSY_D, "personaje");
		double	x_3 = validarDouble("x3", personaje, POSX_D, "personaje");
		double	y_3 = validarDouble("y3", personaje, POSY_D, "personaje");
		double	x_4 = validarDouble("x4", personaje, POSX_D, "personaje");
		double	y_4 = validarDouble("y4", personaje, POSY_D, "personaje");
		//}
		double posiciones[] = {x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4};
		int cantidadJugadores = validarInt("cantidadJugadores", escenario,
				CANTIDADJUGADORES_D, "escenario");
		if (cantidadJugadores <= 0)
			cantidadJugadores = CANTIDADJUGADORES_D;

		string nombreMapa = validarNombreMapa("nombreMapa", escenario,
				string("Un mapa"), "escenario");

		string siguienteNivel = validarNombreMapa("siguienteNivel",escenario,ESCENARIO_X_DEFECTO,"escenario");

		int minJugadores = validarInt("minJugadores",escenario,MIN_JUG,"escenario");

		this->elEscenario->configurarEscenerio(altopx, anchopx, altoun, anchoun,
				imagen, x, y, cantidadJugadores, nombreMapa,siguienteNivel,minJugadores,posiciones);
		this->obtenerObjetos(escenario);
	}

}

int genRand(int max) {
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	return (rand() % max);
}

int LectorJson::validarComunes(Value objeto, double *posx, double *posy,
		double *rot, double *masa, string *color, double *escala, bool *estado,
		string codigoObjeto) {
	double x = this->validarDouble("x", objeto, POS_OBJ_INV, codigoObjeto);
	double y = this->validarDouble("y", objeto, POS_OBJ_INV, codigoObjeto);
	if (x == POS_OBJ_INV || y == POS_OBJ_INV) {
		return INVALIDO;
	}
	double rotacion = this->validarDouble("rot", objeto, ROT_OBJ_D,
			codigoObjeto);
	if (rotacion < 0 || rotacion > 360) {
		logger->reportarProblema(
				"La rotacion requerida no se permite. Se establece rotacion por defecto.",
				WARNING);
		rotacion = ROT_OBJ_D;
	}
	double mass = this->validarDouble("masa", objeto, MASA_OBJ_D, codigoObjeto);
	if (mass < 0) {
		logger->reportarProblema(
				"La masa es negativa. Se establece masa por defecto.", WARNING);
		mass = MASA_OBJ_D;
	}
	string col = this->validarColor("color", objeto, COLOR_OBJ_D, codigoObjeto);

	bool state = this->validarBool("estatico", objeto, EST_OBJ_D, codigoObjeto);
	*posx = x;
	*posy = y;
	*rot = rotacion;
	*masa = mass;
	*color = col;
	*estado = state;
	return OK;
}

void LectorJson::armarRectangulo(Value objeto) {
	double posx, posy, rot, masa, escala;
	string color;
	bool estado;
	if (INVALIDO
			== this->validarComunes(objeto, &posx, &posy, &rot, &masa, &color,
					&escala, &estado, "rectangulo")) {
		logger->reportarProblema(
				"La posicion es invalida, no se puede colocar el objeto rectangulo.",
				WARNING);
		return;
	}

	double alto = this->validarDouble("alto", objeto, ALTO_OBJ_D, "rectangulo");
	if (alto <= 0) {
		logger->reportarProblema(
				"La altura del rectangulo no puede ser menor o igual a 0. Se establece altura por defecto.",
				WARNING);
		alto = ALTO_OBJ_D;
	}
	double ancho = this->validarDouble("ancho", objeto, ANCHO_OBJ_D,
			"rectangulo");
	if (ancho <= 0) {
		logger->reportarProblema(
				"El ancho del rectangulo no puede ser menor o igual a 0. Se establece ancho por defecto.",
				WARNING);
		ancho = ALTO_OBJ_D;
	}
	elEscenario->agregarObjeto("rect", posx, posy, color, rot, masa, escala,
			estado, alto, ancho, 0, 0, 0, 0, 0, 0);
}

void LectorJson::armarPoligon(Value objeto) {
	double posx, posy, rot, masa, escala;
	string color;
	bool estado;
	if (INVALIDO
			== this->validarComunes(objeto, &posx, &posy, &rot, &masa, &color,
					&escala, &estado, "poligono")) {
		logger->reportarProblema(
				"La posicion es invalida, no se puede colocar el objeto poligono.",
				WARNING);
		return;
	}
	int lados = this->validarInt("lados", objeto, LADOS_OBJ_D, "poligono");
	if (lados < 3 || lados > 6) {
		logger->reportarProblema(
				"La cantidad de lados es invalida. Se carga defecto", WARNING);
		lados = LADOS_OBJ_D;
	}
	double scale = this->validarDouble("escala", objeto, ESCALA_OBJ_D,
			"poligono");
	if (scale <= 0) {
		logger->reportarProblema(
				"La escala es negativa. Se establece escala por defecto.",
				WARNING);
		scale = ESCALA_OBJ_D;
	}
	elEscenario->agregarObjeto("poli", posx, posy, color, rot, masa, scale,
			estado, 0, 0, lados, 0, 0, 0, 0, 0);
}

void LectorJson::armarCirculo(Value objeto) {
	double posx, posy, rot, masa, escala;
	string color;
	bool estado;
	if (INVALIDO
			== this->validarComunes(objeto, &posx, &posy, &rot, &masa, &color,
					&escala, &estado, "circulo")) {
		logger->reportarProblema(
				"La posicion es invalida, no se puede colocar el objeto circulo.",
				WARNING);
		return;
	}
	double radio = this->validarDouble("radio", objeto, RADIO_OBJ_D, "circulo");
	if (radio <= 0) {
		logger->reportarProblema(
				"El radio es invalido. Se carga el radio por defecto", WARNING);
		radio = RADIO_OBJ_D;
	}
	elEscenario->agregarObjeto("circ", posx, posy, color, rot, masa, escala,
			estado, 0, 0, 0, radio, 0, 0, 0, 0);
}

void LectorJson::armarParalelogramo(Value objeto) {
	double posx, posy, rot, masa, escala;
	string color;
	bool estado;
	if (INVALIDO
			== this->validarComunes(objeto, &posx, &posy, &rot, &masa, &color,
					&escala, &estado, "paralelogramo")) {
		logger->reportarProblema(
				"La posicion es invalida, no se puede colocar el objeto paralelogramo.",
				WARNING);
		return;
	}
	double baseParal = this->validarDouble("base", objeto, BASE_OBJ_D,
			"paralelogramo");
	if (baseParal <= 0) {
		logger->reportarProblema(
				"La base del paralelogramo es negativa. Se carga defecto",
				WARNING);
		baseParal = BASE_OBJ_D;
	}
	double alto = this->validarDouble("alto", objeto, ALTO_OBJ_D,
			"paralelogramo");
	if (alto <= 0) {
		logger->reportarProblema(
				"La altura del paralelogramo no puede ser menor o igual a 0. Se establece altura por defecto.",
				WARNING);
		alto = ALTO_OBJ_D;
	}
	double angulo = this->validarDouble("angulo", objeto, ANGULO_OBJ_D,
			"paralelogramo");
	if (angulo < -180 || angulo > 180) {
		logger->reportarProblema(
				"El angulo para le paralelogramo es invalido. Se carga defecto",
				WARNING);
		angulo = ANGULO_OBJ_D;
	}
	angulo = angulo / 180 * 3.141;
	elEscenario->agregarObjeto("paral", posx, posy, color, rot, masa, escala,
			estado, alto, 0, 0, 0, baseParal, angulo, 0, 0);
}

void LectorJson::armarTrapecio(Value objeto) {
	double posx, posy, rot, masa, escala;
	string color;
	bool estado;
	if (INVALIDO
			== this->validarComunes(objeto, &posx, &posy, &rot, &masa, &color,
					&escala, &estado, "trapecio")) {
		logger->reportarProblema(
				"La posicion es invalida, no se puede colocar el objeto trapecio.",
				WARNING);
		return;
	}
	double baseMayor = this->validarDouble("base_superior", objeto,
			BASE_SUPERIOR_OBJ_D, "trapecio");
	if (baseMayor <= 0) {
		logger->reportarProblema(
				"La base superior del trapecio es invalida. Se carga defecto",
				WARNING);
		baseMayor = BASE_SUPERIOR_OBJ_D;
	}
	double baseMenor = this->validarDouble("base_inferior", objeto,
			BASE_INFERIOR_OBJ_D, "trapecio");
	if (baseMenor <= 0) {
		logger->reportarProblema(
				"La base inferior del trapecio es invalida. Se carga defecto",
				WARNING);
		baseMayor = BASE_INFERIOR_OBJ_D;
	}
	double angulo = this->validarDouble("angulo", objeto, ANGULO_OBJ_D,
			"trapecio");
	if (angulo < 0 || angulo > 180) {
		logger->reportarProblema(
				"El angulo para le trapecio es invalido. Se carga defecto",
				WARNING);
		angulo = ANGULO_OBJ_D;
	}
	double alto = this->validarDouble("alto", objeto, ALTO_OBJ_D, "trapecio");
	if (alto <= 0) {
		logger->reportarProblema(
				"La altura del trapecio no puede ser menor a 0. Se establece altura por defecto.",
				WARNING);
		alto = ALTO_OBJ_D;
	}

	angulo = angulo / 180 * 3.141;
	elEscenario->agregarObjeto("trap", posx, posy, color, rot, masa, escala,
			estado, alto, 0, 0, 0, 0, angulo, baseMayor, baseMenor);
}

void LectorJson::obtenerObjetos(Value raiz) {
	Value objetos = raiz["objetos"];
	if (objetos.isNull()) {
		logger->reportarProblema("El Escenario no contiene objetos.", WARNING);
		return;
	}
	for (unsigned int i = 0; i < objetos.size(); i++) {
		crearObjeto(objetos[i]);
	}
}

void LectorJson::crearObjeto(Value objeto) {
	Value tipo = objeto["tipo"];
	if (tipo.isNull()) {
		logger->reportarProblema(
				"El Tipo del objeto no esta definido, no se puede crear.",
				WARNING);
	} else {
		string tipo_s = tipo.asString();
		if (tipo_s == "rect")
			this->armarRectangulo(objeto);
		else if (tipo_s == "poli")
			this->armarPoligon(objeto);
		else if (tipo_s == "circ")
			this->armarCirculo(objeto);
		else if (tipo_s == "paral")
			this->armarParalelogramo(objeto);
		else if (tipo_s == "trap")
			this->armarTrapecio(objeto);
		else
			logger->reportarProblema(
					"Tipo de objeto '" + tipo.asString()
							+ "' no esta definido, no se puede crear.",
					WARNING);
	}
}

void LectorJson::cargarEscenario(const char* rutaArchivo) {
	ifstream archivoJson(rutaArchivo, std::ifstream::binary);
	if (!archivoJson.good()) {
		if (!strcmp(rutaArchivo, ESCENARIO_X_DEFECTO)) {
			logger->reportarProblema(
					"Escenario por defecto no existe. Debe crear un mapa por defecto.",
					FATAL);
			exit(0);
		} else {
			logger->reportarProblema(
					"No se encuentra la ruta especificada. Carga Escenario por defecto.",
					ERROR);
			this->cargarEscenario(ESCENARIO_X_DEFECTO);
			return;
		}
	} else {
		if (archivoJson.get() != '{') {
			logger->reportarProblema(
					"El escenario que se quiere cargar esta corrupto en: Line 1, Column 1. Carga Escenario por defecto.",
					ERROR);
			this->cargarEscenario(ESCENARIO_X_DEFECTO);
			return;
		}
		archivoJson.unget();
		Reader lector;
		Value raiz;
		bool parseExitoso = lector.parse(archivoJson, raiz, false);
		if (!parseExitoso) {
			string errores = lector.getFormatedErrorMessages();
			logger->reportarProblema(
					"Error de parseo en:" + errores
							+ "Carga Escenario por defecto", ERROR);
			this->cargarEscenario(ESCENARIO_X_DEFECTO);
			return;
		} else {
			this->obtenerEscenario(raiz);
			//this->elEscenario->imprimirXConsola();
		}
	}
}

