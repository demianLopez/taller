/*
 * UpdateRequest.h
 *
 *  Created on: 02/11/2014
 *      Author: demian
 */

#ifndef UPDATEREQUEST_H_
#define UPDATEREQUEST_H_

class UpdateRequest {
public:
	int index;
	float posX;
	float posY;
	float rotation;
	int animation;
	UpdateRequest();
	virtual ~UpdateRequest();
};

#endif /* UPDATEREQUEST_H_ */
