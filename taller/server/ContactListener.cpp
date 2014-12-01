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

	Personaje *aPlayer;
	Polygon *aPolygon;

	// Para ver si puede saltar
	if (first->type == ContactContainer::SENSORDELPIE
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Personaje*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& second->type == ContactContainer::SENSORDELPIE) {
		aPlayer = (Personaje*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		return;
	}

	// Contacto enemigo/jugador
	if (first->type == ContactContainer::ENEMY
			&& second->type == ContactContainer::JUGADOR) {
		aPlayer = (Personaje*) second->containedThing;
		if(!((Enemigo *) first->containedThing)->isInmovil()){
			aPlayer->hit();
		}
		return;
	}
	if (first->type == ContactContainer::JUGADOR
			&& second->type == ContactContainer::ENEMY) {
		aPlayer = (Personaje*) first->containedThing;
		if(!((Enemigo *) second->containedThing)->isInmovil()){
			aPlayer->hit();
		}
		return;
	}

	// Atravezar rampas desde abajo
	if (first->type == ContactContainer::SENSORDELACABEZA
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Personaje*) first->containedThing;
		aPolygon = (Polygon*) second->containedThing;
		aPlayer->getHeadListener()->addHeadContact(aPolygon);
		return;
	}
	if (first->type == ContactContainer::POLYGON
				&& second->type == ContactContainer::SENSORDELACABEZA) {
			aPlayer = (Personaje*) second->containedThing;
			aPolygon = (Polygon*) first->containedThing;
			aPlayer->getHeadListener()->addHeadContact(aPolygon);
			return;
	}
	if ( (first->type == ContactContainer::JUGADOR
			|| first->type == ContactContainer::ENEMY)
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Personaje*) first->containedThing;
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
		aPlayer = (Personaje*) second->containedThing;
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

