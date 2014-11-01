/*
 * Data.h
 *
 *  Created on: 01/11/2014
 *      Author: demian
 */

#ifndef DATA_H_
#define DATA_H_

#include "Server.h"
#include "World.h"

class Data {
public:
	static Server * server;
	static World * world;
};

#endif /* DATA_H_ */
