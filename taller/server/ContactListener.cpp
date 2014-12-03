#include "ContactListener.h"
#include "ContactContainer.h"
#include "Jugador.h"
#include "Disparo.h"
#include "Enemigo.h"
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

ContactListener::ContactListener() {
	numberOfContacts = 0;
}

bool canGoThrough(Personaje* aPlayer, Polygon* aPolygon){
	return aPlayer->getHeadListener()->isHeadTouching(aPolygon);
}

void ContactListener::BeginContact(b2Contact* contact) {
	ContactContainer* first =
			(ContactContainer*) contact->GetFixtureA()->GetUserData();
	ContactContainer* second =
			(ContactContainer*) contact->GetFixtureB()->GetUserData();

	if (first == NULL || second == NULL)
		return;

	Jugador *aPlayer;
	Polygon *aPolygon;

	// Para ver si puede saltar
	if (first->type == ContactContainer::SENSORDELPIE
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& second->type == ContactContainer::SENSORDELPIE) {
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		return;
	}

	// Contacto enemigo/jugador
	if (first->type == ContactContainer::ENEMY
			&& second->type == ContactContainer::JUGADOR) {
		aPlayer = (Jugador *) second->containedThing;
		Enemigo * enemy = (Enemigo *)first->containedThing;
		if(!enemy->isInmovil()){
			aPlayer->hit();
		}

		aPlayer->touchingEnemy(enemy);
		return;
	}
	if (first->type == ContactContainer::JUGADOR
			&& second->type == ContactContainer::ENEMY) {
		aPlayer = (Jugador*) first->containedThing;
		Enemigo * enemy = (Enemigo *)second->containedThing;
		if(!enemy->isInmovil()){
			aPlayer->hit();
		}
		aPlayer->touchingEnemy(enemy);
		return;
	}

	// Atravezar rampas desde abajo
	if (first->type == ContactContainer::SENSORDELACABEZA
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Jugador*) first->containedThing;
		aPolygon = (Polygon*) second->containedThing;
		aPlayer->getHeadListener()->addHeadContact(aPolygon);
		return;
	}
	if (first->type == ContactContainer::POLYGON
				&& second->type == ContactContainer::SENSORDELACABEZA) {
			aPlayer = (Jugador*) second->containedThing;
			aPolygon = (Polygon*) first->containedThing;
			aPlayer->getHeadListener()->addHeadContact(aPolygon);
			return;
	}
	if ( (first->type == ContactContainer::JUGADOR
			|| first->type == ContactContainer::ENEMY)
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Jugador*) first->containedThing;
		aPolygon = (Polygon*) second->containedThing;

		if (canGoThrough(aPlayer, aPolygon)){
			contact->SetEnabled(false);
			aPlayer->atravesandoRampa = true;
		}

		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& (second->type == ContactContainer::JUGADOR
				|| second->type == ContactContainer::ENEMY)) {
		aPlayer = (Jugador*) second->containedThing;
		aPolygon = (Polygon*) first->containedThing;

		if (canGoThrough(aPlayer, aPolygon)){
			contact->SetEnabled(false);
			aPlayer->atravesandoRampa = true;
		}

		return;
	}
	if(first->type == ContactContainer::DISPARO_JUGADOR || second->type == ContactContainer::DISPARO_JUGADOR){
		Disparo * disparo;
		int tipoImpactado;
		void * objetivo;

		if(first->type == ContactContainer::DISPARO_JUGADOR) {
			disparo = (Disparo *) first->containedThing;
			tipoImpactado = second->type;
			objetivo = second->containedThing;
		} else {
			disparo = (Disparo *) second->containedThing;
			tipoImpactado = first->type;
			objetivo = first->containedThing;
		}

		disparo->destroy();

		if(tipoImpactado == ContactContainer::ENEMY){
			Enemigo * e;
			e = (Enemigo *) objetivo;
			e->hit();
		}

		return;
	}
	if (first->type == ContactContainer::SNOW_BALL_ENEMY
			|| second->type == ContactContainer::SNOW_BALL_ENEMY) {
		Enemigo * enemy;
		int tipoOtro;
		void * otroObjetivo;
		if(first->type == ContactContainer::SNOW_BALL_ENEMY){
			enemy = (Enemigo*)first->containedThing;
			tipoOtro = second->type;
			otroObjetivo = second->containedThing;
		} else {
			enemy = (Enemigo*)second->containedThing;
			tipoOtro = first->type;
			otroObjetivo = first->containedThing;
		}

		switch(tipoOtro){
			/*case ContactContainer::POLYGON:
			{
				Polygon * p = (Polygon*)otroObjetivo;
				float posy = enemy->getPosition()->y -p->getPosition()->y;

				if(posy < 0.5 && posy > -0.5){
					enemy->golpeadoPorBola(NULL);
				}
				break;
			}*/
			case ContactContainer::ENEMY:
			{
				Enemigo * impactado = (Enemigo*)otroObjetivo;
				impactado->golpeadoPorBola(enemy);
				break;
			}
		}

	}




}

void ContactListener::EndContact(b2Contact* contact) {
	ContactContainer* first =
			(ContactContainer*) contact->GetFixtureA()->GetUserData();
	ContactContainer* second =
			(ContactContainer*) contact->GetFixtureB()->GetUserData();

	if (first == NULL || second == NULL)
		return;

	Personaje *aPlayer;
	Polygon *aPolygon;

	if (first->type == ContactContainer::SENSORDELPIE
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Personaje*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts--;
		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& second->type == ContactContainer::SENSORDELPIE) {
		aPlayer = (Personaje*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts--;
		return;
	}

	// Atravezar rampas desde abajo
	if (first->type == ContactContainer::SENSORDELACABEZA
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Personaje*) first->containedThing;
		aPolygon = (Polygon*) second->containedThing;
		aPlayer->getHeadListener()->removeHeadContact(aPolygon);
		return;
	}
	if (first->type == ContactContainer::POLYGON
				&& second->type == ContactContainer::SENSORDELACABEZA) {
			aPlayer = (Personaje*) second->containedThing;
			aPolygon = (Polygon*) first->containedThing;
			aPlayer->getHeadListener()->removeHeadContact(aPolygon);
			return;
	}
	if (first->type == ContactContainer::ENEMY
			&& second->type == ContactContainer::JUGADOR) {
		Jugador *p = (Jugador *) second->containedThing;
		p->touchingEnemy(NULL);
	}
	if (first->type == ContactContainer::JUGADOR
			&& second->type == ContactContainer::ENEMY) {
		Jugador *p = (Jugador *) first->containedThing;
		p->touchingEnemy(NULL);
	}
	if ( (first->type == ContactContainer::JUGADOR
			|| first->type == ContactContainer::ENEMY)
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Personaje*) first->containedThing;
		aPlayer->atravesandoRampa = false;

		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& (second->type == ContactContainer::JUGADOR
				|| second->type == ContactContainer::ENEMY)) {
		aPlayer = (Personaje*) second->containedThing;
		aPlayer->atravesandoRampa = false;
		return;
	}
}

int ContactListener::getNumberOfContacts() {
	return numberOfContacts;
}

void ContactListener::addHeadContact(Polygon* aPolygon){
	polygonsInContact[aPolygon] = true;
}

bool ContactListener::isHeadTouching(Polygon* aPolygon){
	return !(polygonsInContact.find(aPolygon) == polygonsInContact.end());
}

void ContactListener::removeHeadContact(Polygon* aPolygon){
	polygonsInContact.erase(aPolygon);
}

