#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"
#include "CosaConMovimiento.h"

Personaje::Personaje(b2World * gameWorld) : CosaConMovimiento(gameWorld){

}

Personaje::~Personaje(){
	//delete this->mainCharacterBody;
}




