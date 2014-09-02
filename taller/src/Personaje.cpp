#include "Personaje.h"

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
// por la velocidad maxima.
void Personaje::acelerarPersonaje(float x, float y){
	velocidad.aumentarEn(x,y);

	// Limite de velocidad en X
	limitarVelocidad(&velocidad.x, velocidadMaximaX);

	// Limite de velocidad en Y
	limitarVelocidad(&velocidad.y, velocidadMaximaY);
}




