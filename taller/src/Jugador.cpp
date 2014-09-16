#include "Jugador.h"

// Inicializa Jugador.
Jugador::Jugador(b2World * gameWorld) : Personaje(gameWorld) {
	//Defino forma, posicion y tamanyo del body para el Personaje.

	// TODO: permitir ponerlo en una posicion especifica.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(8.0f, 10.0f);

	body = gameWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f); //TODO: mejorar medidas.

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0;

	body->CreateFixture(&fixtureDef);

	// Redefino velocidades a las ajustadas para el jugador principal.
	movementSpeedX = MOVEMENT_SPEED_X;
	movementSpeedY = MOVEMENT_SPEED_Y;

	//buffVelocidad = false;
}

// Devuelve true si tiene buff de velocidad.
/*
bool Jugador::tieneBuffVelocidad(){
	return buffVelocidad;
}
*/

// Le otorga el buff de velocidad.
/*
void Jugador::darBuffVelocidad(){
	velocidadMaximaX = VELOCIDAD_MAXIMA_BUFF_X;
	buffVelocidad = true;
}
*/

// Le quita el buff de velocidad.
/*
void Jugador::quitarBuffVelocidad(){
	velocidadMaximaX = VELOCIDAD_MAXIMA_DEFAULT_X;
	buffVelocidad = false;
}
*/

/*
BolaDeNieve Jugador::disparar(){
	return BolaDeNieve(estaMirandoParaLaDerecha(), posicion);
}
*/
