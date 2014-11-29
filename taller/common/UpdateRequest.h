/*
 * UpdateRequest.h
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#ifndef UPDATEREQUEST_H_
#define UPDATEREQUEST_H_
#include "CommandCode.h"

class UpdateRequest {
public:
	int index;
	float posX;
	float posY;
	float rotation;
	AnimationCode animation;
	bool offline;
	bool invulnerable;
	UpdateRequest();
	virtual ~UpdateRequest();
};

#endif /* UPDATEREQUEST_H_ */
