#include <ContactListener.h>

ContactListener::ContactListener(){
	numberOfContacts = 0;
}


void ContactListener::BeginContact(b2Contact* contact){
	void* data = contact->GetFixtureA()->GetUserData();
	if( (int) data == 2){
		numberOfContacts++;
	}

	data = contact->GetFixtureB()->GetUserData();
	if( (int) data == 2){
		numberOfContacts++;
	}
}

void ContactListener::EndContact(b2Contact* contact){
	void* data = contact->GetFixtureA()->GetUserData();
	if( (int) data == 2){
		numberOfContacts--;
	}

	data = contact->GetFixtureB()->GetUserData();
	if( (int) data == 2){
		numberOfContacts--;
	}
}

int ContactListener::getNumberOfContacts(){
	return numberOfContacts;
}
