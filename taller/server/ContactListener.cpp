#include "ContactListener.h"
#include "ContactContainer.h"
#include "Jugador.h"
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

ContactListener::ContactListener() {
	numberOfContacts = 0;
}

void ContactListener::BeginContact(b2Contact* contact) {
	ContactContainer* first = (ContactContainer*) contact->GetFixtureA()->GetUserData();
	ContactContainer* second = (ContactContainer*) contact->GetFixtureB()->GetUserData();

	if(first == NULL || second == NULL) return;

	Jugador *aPlayer;
	/*
	printf("%p  -  %p\n", first, second);
	cout << "--" << endl;
	if(first->type == ContactContainer::JUGADOR) cout << "First es jugador" << endl;
	if(second->type == ContactContainer::JUGADOR) cout << "Second es jugador" << endl;
	if(first->type == ContactContainer::POLYGON) cout << "First es polygon" << endl;
	if(second->type == ContactContainer::POLYGON) cout << "Second es polygon" << endl;
	if(first->type == ContactContainer::SENSORDELPIE) cout << "First es sensor" << endl;
	if(second->type == ContactContainer::SENSORDELPIE) cout << "Second es sensor" << endl;
	cout << "--" << endl;
	*/
	if(first->type == ContactContainer::JUGADOR && second->type == ContactContainer::POLYGON){
		aPlayer = (Jugador*) first->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		cout << "SHDASHD " << aPlayer->getListenerTouchingGround()->getNumberOfContacts() << endl;
		return;
	}
	if(first->type == ContactContainer::POLYGON && second->type == ContactContainer::JUGADOR){
		aPlayer = (Jugador*) second->containedThing;
		aPlayer->getListenerTouchingGround()->numberOfContacts++;
		cout << "SHDASHD " << aPlayer->getListenerTouchingGround()->getNumberOfContacts() << endl;
	}


}

void ContactListener::EndContact(b2Contact* contact) {
	ContactContainer* first = (ContactContainer*) contact->GetFixtureA()->GetUserData();
	ContactContainer* second = (ContactContainer*) contact->GetFixtureB()->GetUserData();

	if(first == NULL || second == NULL) return;

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
