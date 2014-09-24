#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_

#include "Box2D/Box2D.h"

class ContactListener: public b2ContactListener {
private:
	int numberOfContacts;
public:
	ContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	int getNumberOfContacts();
};

#endif /* CONTACTLISTENER_H_ */
