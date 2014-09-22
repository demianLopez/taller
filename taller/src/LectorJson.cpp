/*
 * LectorJson.cpp
 *
 *  Created on: 18/9/2014
 *      Author: FireHorse
 */

#include <LectorJson.h>

//Escenario por defecto
const char* ESCENARIO_X_DEFECTO = "Resources/escenario.json";

//Valores por defecto escenario
const int ALTOPX_D = 720;
const int ANCHOPX_D = 1024;
const int ALTOUN_D = 100;
const int ANCHOUN_D = 50;
const string IMAGEN_FONDO_D = "Resources/font1.png";

//Valores por defecto personaje
const int POSX_D = 100;
const int POSY_D = 100;

//Valores por defecto objeto
const double POSX_OBJ_D = 5.0;
const double POSY_OBJ_D = 90.0;
const double ANCHO_OBJ_D = 1.0;
const double ALTO_OBJ_D = 1.0;
const int LADOS_OBJ_D = 3;
const double RADIO_OBJ_D = 3.0;
const double BASE_OBJ_D = 2.0;
const string COLOR_OBJ_D = "#00FF00";
const double ROT_OBJ_D = 45;
const double MASA_OBJ_D = 1.0;
const bool EST_OBJ_D = true;

//Tipo de problemas
const int ERROR = 1;
const int WARNING = 2;
const int FATAL = 3;


LectorJson::LectorJson() {
	logger = new LogManager();
	elEscenario = new GestorEscenario();
	// TODO Auto-generated constructor stub

}

LectorJson::~LectorJson() {
	delete logger;
	delete elEscenario;
	// TODO Auto-generated destructor stub
}

int LectorJson::validarInt(string miembro, Value raiz, int valorDefecto){
	Value clave = raiz[miembro];
	if( clave.isNull()){
		logger->reportarProblema("No existe el miembro "+miembro+ " en " + raiz.asString()+
				". Cargo entero por defecto.",WARNING);
		return valorDefecto;
	}
	if (!clave.isInt()){
		logger->reportarProblema("El miembro "+miembro+ " no es entero. "+". Cargo entero por defecto." ,WARNING);
		return valorDefecto;
		}
	return (clave.asInt());
}

double LectorJson::validarDouble(string miembro, Value raiz, double valorDefecto){
	Value clave = raiz[miembro];
	if( clave.isNull()){
		logger->reportarProblema("No existe el miembro "+miembro+ " en " + raiz.asString()+
				". Cargo double por defecto.",WARNING);
		return valorDefecto;
	}
	if (!clave.isDouble()){
		logger->reportarProblema("El miembro "+miembro+ " no es double. "+". Cargo double por defecto." ,WARNING);
		return valorDefecto;
		}
	return (clave.asDouble());
}

bool LectorJson::validarBool(string miembro,Value raiz, bool valorDefecto){
	Value boolean = raiz[miembro];
	if( boolean.isNull()){
		logger->reportarProblema("No existe el miembro "+miembro+ " en " + raiz.asString()+
					". Cargo booleano por defecto.",WARNING);
		return valorDefecto;
		}
	if (!boolean.isBool()){
		logger->reportarProblema("El miembro "+miembro+ "no es booleano. Cargo booleano por defecto." ,WARNING);
		return valorDefecto;
		}
	return (boolean.asBool());
}


string LectorJson::validarColor(string miembro,Value raiz, string valorDefecto){
	Value color = raiz[miembro];
	if(color.isNull()){
		logger->reportarProblema("No existe el miembro "+miembro+ " en " + raiz.asString()+
						". Cargo color por defecto.",WARNING);
		return valorDefecto;
	}
	if (!color.isString()){
		logger->reportarProblema("Formato de color invalido en " + raiz["tipo"].asString()+//para obtener color debe exitir tipo
								". Cargo color por defecto.",WARNING);
		return valorDefecto;
	}
	if(!((color.asString().size() == 7)&&(color.asString()[0] == '#'))){
		logger->reportarProblema("Formato de color invalido en " + raiz["tipo"].asString()+//para obtener color debe exitir tipo
										". Cargo color por defecto.",WARNING);
		return valorDefecto;
	}
	string col = color.asString();
	for(unsigned int i=1 ; i < color.asString().size() ; i++){
		if(!((int(col[i]) >= 48 && int(col[i]) <= 57) || (int(col[i]) >= 65 && int(col[i]) <= 70))){
			string e1 = "Valor<";
			e1 += col[i];
			e1 += "> en posicion ";
			e1 += char(i);
			logger->reportarProblema(e1+" no es valido. Se coloca por defecto F",WARNING);
			col[i] = 'F';
		}
	}
	return col;
}

string LectorJson::validarImagen(string miembro,Value raiz, string valorDefecto){
	Value imagen = raiz[miembro];
	if(imagen.isNull()){
		logger->reportarProblema("No existe el miembro "+miembro+ " en " + raiz.asString()+
							". Cargo imagen por defecto.",WARNING);
		return valorDefecto;
	}
	if (!imagen.isString()){
		logger->reportarProblema("Formato de imagen invalido. Carga imgen por defecto", WARNING);
		return valorDefecto;
	}
	ifstream imagenFondo(imagen.asString(), std::ifstream::binary);
	if(!imagenFondo.good()){
		if( imagen.asString() == valorDefecto){
			logger->reportarProblema("No existe imagen por defecto, debe crear una.", FATAL);
			exit(0);
		}
		else{
			logger->reportarProblema("La ruta de la imagen de fondo no existe. Carga imagen por defecto.", WARNING);
			return valorDefecto;
		}
	}
	return (imagen.asString());
}

void LectorJson::obtenerEscenario(Value raiz){
	Value escenario = raiz["escenario"];
	if(escenario.isNull()){
		logger->reportarProblema("No se encontro la clave 'escenario'. Carga Escenario por defecto.",ERROR);
		this->cargarEscenario(ESCENARIO_X_DEFECTO);
		return;
	}
	else{
		int altopx = validarInt("altopx",escenario,ALTOPX_D);
		int anchopx = validarInt("anchopx",escenario,ALTOPX_D);
		int altoun = validarInt("altoun",escenario,ALTOPX_D);
		int anchoun = validarInt("anchoun",escenario,ALTOPX_D);
		string imagen = validarImagen("imagen_fondo",escenario,IMAGEN_FONDO_D);
		Value personaje = escenario["personaje"];
		int x;
		int y;
		if(personaje.isNull()){
			logger->reportarProblema("No se encontro clave 'personaje'. Carga personaje por defecto.",WARNING);
			x = POSX_D;
			y = POSY_D;
		}
		else{
			x = validarInt("x",personaje,POSX_D);
			y = validarInt("y",personaje,POSY_D);
		}
		this->elEscenario->configurarEscenerio(altopx,anchopx,altoun,anchoun,imagen,x,y);
		this->elEscenario->imprimirXConsola();
	}

}

void LectorJson::validarComunes(Value objeto,double *posx,double *posy,double *rot,double *masa,string color,bool *estado){
	Value valor = objeto["x"];
	if(valor.isNull()){
		logger->reportarProblema("No se declara la posicion en x para el objeto. Se genera una.",WARNING);

	}
}

void LectorJson::armarRectangulo(Value objeto){
	double posx,posy,rot,masa;
	string color;
	bool estado;
	this->validarComunes(objeto,&posx,&posy,&rot,&masa,color,&estado);
}

void LectorJson::armarPoligon(Value objeto){

}

void LectorJson::armarCirculo(Value objeto){

}

void LectorJson::armarParalelogramo(Value objeto){

}

void LectorJson::armarTrapecio(Value objeto){

}

void LectorJson::obtenerObjetos(Value raiz){
	Value objetos = raiz["objetos"];
	if(objetos.isNull()){
		logger->reportarProblema("El Escenario no contiene objetos.", WARNING);
		return;
	}
	for(unsigned int i = 0; i < objetos.size(); i++){
		crearObjeto(objetos[i]);
	}
}

void LectorJson::crearObjeto(Value objeto){
	Value tipo = objeto["tipo"];
	if(tipo.isNull()){
		logger->reportarProblema("El Tipo del objeto no esta definido, no se puede crear", WARNING);
	}
	else{
		string tipo_s = tipo.asString();
		if (tipo_s=="rect")
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
			logger->reportarProblema("Tipo de objeto "+tipo.asString()+" no esta definido, no se puede crear", WARNING);
		}
}

void LectorJson::cargarEscenario(const char* rutaArchivo){
	this->logger->setearFecha();
	ifstream archivoJson(rutaArchivo, std::ifstream::binary);
	if(!archivoJson.good()){
		if( !strcmp(rutaArchivo,ESCENARIO_X_DEFECTO)){
			logger->reportarProblema("Escenario por defecto no existe. Debe crear un mapa por defecto.", FATAL);
			exit(0);
		}
		else{
			logger->reportarProblema("No se encuentra la ruta especificada. Carga Escenario por defecto.", ERROR);
			this->cargarEscenario(ESCENARIO_X_DEFECTO);
			return;
		}
	}
	else{
		Reader lector;
		Value raiz;
		bool parseExitoso = lector.parse(archivoJson, raiz, false );
		if (!parseExitoso){
			logger->reportarProblema("Error de parseo. Carga Escenario por defecto", ERROR);
			this->cargarEscenario(ESCENARIO_X_DEFECTO);
			return;
		}
		else{
			this->obtenerEscenario(raiz);
			this->obtenerObjetos(raiz);
		}
	}
}
