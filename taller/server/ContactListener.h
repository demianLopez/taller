#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_

#include <map>
using std::map;
using std::pair;

#include "Box2D/Box2D.h"
#include "polygons/Polygon.h"

class ContactListener: public b2ContactListener {
public:
	int numberOfContacts;
	map<Polygon*,bool> polygonsInContact;
	ContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	int getNumberOfContacts();

	void addHeadContact(Polygon* aPolygon);
	bool isHeadTouching(Polygon* aPolygon);
	void removeHeadContact(Polygon* aPolygon);
};

#endif /* CONTACTLISTENER_H_ */
