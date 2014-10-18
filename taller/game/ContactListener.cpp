#include "ContactListener.h"

ContactListener::ContactListener() {
	numberOfContacts = 0;
}

void ContactListener::BeginContact(b2Contact* contact) {
	size_t data = (size_t) contact->GetFixtureA()->GetUserData();

	if (data == 2) {
		numberOfContacts++;
	}

	data = (size_t) contact->GetFixtureB()->GetUserData();
	if (data == 2) {
		numberOfContacts++;
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	size_t data = (size_t) contact->GetFixtureA()->GetUserData();
	if (data == 2) {
		numberOfContacts--;
	}

	data = (size_t) contact->GetFixtureB()->GetUserData();
	if (data == 2) {
		numberOfContacts--;
	}
}

int ContactListener::getNumberOfContacts() {
	return numberOfContacts;
}
