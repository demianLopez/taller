#include "Jugador.h"

// Inicializa Jugador quieto en (x,y), (0,0) por defecto.
Jugador::Jugador(float x, float y) {
	posicion.set(x,y);
	velocidad.set(0,0);
	velocidadMaximaX = VELOCIDAD_MAXIMA_DEFAULT_X;
	velocidadMaximaY = VELOCIDAD_MAXIMA_DEFAULT_Y;
	buffVelocidad = false;
}

// Devuelve true si tiene buff de velocidad.
bool Jugador::tieneBuffVelocidad(){
	return buffVelocidad;
}

// Le otorga el buff de velocidad.
void Jugador::darBuffVelocidad(){
	velocidadMaximaX = VELOCIDAD_MAXIMA_BUFF_X;
	buffVelocidad = true;
}

// Le quita el buff de velocidad.
void Jugador::quitarBuffVelocidad(){
	velocidadMaximaX = VELOCIDAD_MAXIMA_DEFAULT_X;
	buffVelocidad = false;
}

BolaDeNieve Jugador::disparar(){
	return BolaDeNieve(estaMirandoParaLaDerecha(), posicion);
}
