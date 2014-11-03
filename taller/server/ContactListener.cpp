#include "ContactListener.h"
#include "ContactContainer.h"
#include "Jugador.h"

ContactListener::ContactListener() {
	numberOfContacts = 0;
}

void ContactListener::BeginContact(b2Contact* contact) {
	ContactContainer* first = (ContactContainer*) contact->GetFixtureA()->GetUserData();
	ContactContainer* second = (ContactContainer*) contact->GetFixtureA()->GetUserData();
	if(first == NULL || second == NULL) return;
	//if (first == 3 || second == 3) return; //Es un contacto con un contact listener..
	Jugador *aPlayer;
	if(first->type == ContactContainer::JUGADOR && second->type == ContactContainer::POLYGON){
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		return;
	}
	if(first->type == ContactContainer::POLYGON && second->type == ContactContainer::JUGADOR){
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
	}


}

void ContactListener::EndContact(b2Contact* contact) {
	ContactContainer* first = (ContactContainer*) contact->GetFixtureA()->GetUserData();
	ContactContainer* second = (ContactContainer*) contact->GetFixtureA()->GetUserData();

	//if (first == 3 || second == 3) return; //Es un contacto con un contact listener..
	Jugador *aPlayer;
	if(first->type == ContactContainer::JUGADOR && second->type == ContactContainer::POLYGON){
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts--;
		return;
	}
	if(first->type == ContactContainer::POLYGON && second->type == ContactContainer::JUGADOR){
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts--;
	}


}

int ContactListener::getNumberOfContacts() {
	return numberOfContacts;
}
