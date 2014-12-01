#include "ContactListener.h"
#include "ContactContainer.h"
#include "Jugador.h"
#include "polygons/Polygon.h"
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

ContactListener::ContactListener() {
	numberOfContacts = 0;
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
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->hit();
		return;
	}
	if (first->type == ContactContainer::JUGADOR
			&& second->type == ContactContainer::ENEMY) {
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->hit();
		return;
	}

	// Atravezar rampas desde abajo
	if (first->type == ContactContainer::JUGADOR
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Jugador*) first->containedThing;
		aPolygon = (Polygon*) second->containedThing;
		b2Vec2 velocity = aPlayer->getBody()->GetLinearVelocity();
		if (velocity.y > 0){
			contact->SetEnabled(false);
			aPlayer->atravesandoRampa = true;
		}

		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& second->type == ContactContainer::JUGADOR) {
		aPlayer = (Jugador*) second->containedThing;
		aPolygon = (Polygon*) first->containedThing;
		b2Vec2 velocity = aPlayer->getBody()->GetLinearVelocity();
		if(velocity.y > 0){
			contact->SetEnabled(false);
			aPlayer->atravesandoRampa = true;
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

	Jugador *aPlayer;
	if (first->type == ContactContainer::SENSORDELPIE
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts--;
		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& second->type == ContactContainer::SENSORDELPIE) {
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts--;
		return;
	}

	// Atravezar rampas desde abajo
	if (first->type == ContactContainer::JUGADOR
			&& second->type == ContactContainer::POLYGON) {
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->atravesandoRampa = false;

		return;
	}
	if (first->type == ContactContainer::POLYGON
			&& second->type == ContactContainer::JUGADOR) {
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->atravesandoRampa = false;
		return;
	}

}

int ContactListener::getNumberOfContacts() {
	return numberOfContacts;
}
