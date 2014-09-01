#include "Personaje.h"

// Inicializa personaje quieto en (x,y), (0,0) por defecto.
Personaje::Personaje(int x, int y){
	posicion.set(x,y);
	velocidad.set(0,0);
	velocidadMaximaX = VELOCIDAD_MAXIMA_DEFAULT_X;
	velocidadMaximaY = VELOCIDAD_MAXIMA_DEFAULT_Y;
	buffVelocidad = false;
}

// Limita velocidad de coordenada a velocidadMaxima.
void Personaje::limitarVelocidad(float *coordenada, float velocidadMaxima){
	//TODO: Ver que esto funcione como espero.
	if(*coordenada > velocidadMaxima){
		*coordenada = velocidadMaxima;
	}else{
		if(*coordenada < -velocidadMaxima){
			*coordenada = -velocidadMaxima;
		}
	}
}

// Acelera la velocidad del personaje en X e Y. Limitado
// por la velocidad maxima. Devuelve la nueva velocidad.
VectorXY Personaje::acelerarPersonaje(float x, float y){
	velocidad.aumentarEn(x,y);

	// Limite de velocidad en X
	limitarVelocidad(&velocidad.x, velocidadMaximaX);

	// Limite de velocidad en Y
	limitarVelocidad(&velocidad.y, velocidadMaximaY);

}

// Devuelve la posicion actual.
VectorXY Personaje::verPosicionActual(){
	return VectorXY(posicion);
}

// Mueve la posicion del personaje dependiendo de su velocidad.
void Personaje::moverPersonaje(){
	posicion.aumentarEn(velocidad);
}

// Devuelve la posicion a la que se movera el personaje.
VectorXY Personaje::siguientePosicion(){
	return VectorXY(posicion).aumentarEn(velocidad);
}

// Frena al personaje en X y/o Y
void Personaje::frenarPersonaje(bool frenarEnX, bool frenarEnY){
	if (frenarEnX){
		velocidad.x = 0;
	}
	if (frenarEnY){
		velocidad.y = 0;
	}
}

// Devuelve true si tiene buff de velocidad.
bool Personaje::tieneBuffVelocidad(){
	return buffVelocidad;
}

// Le otorga el buff de velocidad.
void Personaje::darBuffVelocidad(){
	velocidadMaximaX = VELOCIDAD_MAXIMA_BUFF_X;
	buffVelocidad = true;
}

// Le quita el buff de velocidad.
void Personaje::quitarBuffVelocidad(){
	velocidadMaximaX = VELOCIDAD_MAXIMA_DEFAULT_X;
	buffVelocidad = false;
}

