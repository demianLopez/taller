/*
 * ContactContainer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: maxi
 */

#include <ContactContainer.h>

ContactContainer::ContactContainer(int typeOfThing, void *contained) {
	type = typeOfThing;
	containedThing = contained;
}
