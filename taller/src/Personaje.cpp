#include "Personaje.h"
#include "Resources.h"
#include "engine/Animation.h"

Personaje::Personaje(b2World * gameWorld){
	//MAIN CHARACTER!
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(8.0f, 10.0f);

	mainCharacterBody = gameWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f); //TODO: mejorar medidas.

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0;

	mainCharacterBody->CreateFixture(&fixtureDef);

	this->stopAtHit = false;

	this->goingUp = false;
	this->goingDown = true;
	this->onTopJump = true;

	//FIXME: ver si eventualmente usamos esto o si lo maneja box2d
	this->velocidadMaximaX = 0;
	this->velocidadMaximaY = 0;
}

b2Body * Personaje::getBody(){
	return this->mainCharacterBody;
}

void Personaje::moveLeft(){
	b2Vec2 currentVel = this->mainCharacterBody->GetLinearVelocity();
	this->mainCharacterBody->SetLinearVelocity(b2Vec2(-4, currentVel.y));
	mirandoParaLaDerecha = false;
}

void Personaje::moveRight(){
	b2Vec2 currentVel = this->mainCharacterBody->GetLinearVelocity();
	this->mainCharacterBody->SetLinearVelocity(b2Vec2(4, currentVel.y));
	mirandoParaLaDerecha = true;
}

bool Personaje::isOnAir(){
	return (this->goingUp || this->goingDown || this->onTopJump);
}

void Personaje::jump(){
	if(!this->isOnAir()){
		b2Vec2 currentVel = this->mainCharacterBody->GetLinearVelocity();
		this->mainCharacterBody->SetLinearVelocity(b2Vec2(currentVel.x, 6));
		this->goingUp = true;
	}
}

void Personaje::stop(bool stopX, bool stopY){
	b2Vec2 currentVel = this->mainCharacterBody->GetLinearVelocity();
	if(stopX){
		this->mainCharacterBody->SetLinearVelocity(b2Vec2(0, currentVel.y));
	}
	if(stopY){
		this->mainCharacterBody->SetLinearVelocity(b2Vec2(currentVel.x, 0));
	}
	// TODO: ver que significaba esto, o que pretendia hacer la funcion.
	/*
	if((currentVel.y < 1 && currentVel.y > -1) && !this->isOnAir()){
		this->mainCharacterBody->SetLinearVelocity(b2Vec2(0, currentVel.y));
	} else {
		this->stopAtHit = true;
	}
	*/
}

Animation * Personaje::getAnimation(Resources * resources){

	//FIXME: deprecated, demi borralo si te parece.
	/*
	if(this->mainCharacterBody->GetLinearVelocity().y < 0){
		//return resources->getPlayerAnimationLeft(); caida libre
	}

	if(this->mainCharacterBody->GetLinearVelocity().x < 0){
		return resources->getPlayerAnimationLeft();
	}

	if(this->mainCharacterBody->GetLinearVelocity().x > 0){
		return resources->getPlayerAnimationRight();
	}
	*/

	if(mirandoParaLaDerecha){
		return resources->getPlayerAnimationRight();
	}
	//else: Esta mirando para la izquierda
	return resources->getPlayerAnimationLeft();
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

void Personaje::update(){
	b2Vec2 currentVel = this->mainCharacterBody->GetLinearVelocity();
	if(currentVel.y < 1 && currentVel.y > -1){
		if(this->goingUp){
			this->goingUp = false;
			this->onTopJump = true;
		}

		if(this->goingDown){
			this->goingDown = false;
			if(stopAtHit){
				this->stop();
				this->stopAtHit = false;
			}
		}

	}

	if(currentVel.y < -1){
		if(this->onTopJump){
			this->onTopJump = false;
			this->goingDown = true;
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

Personaje::~Personaje(){
	//delete this->mainCharacterBody;
}




