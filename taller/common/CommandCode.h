/*
 * CommandCode.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef COMMANDCODE_H_
#define COMMANDCODE_H_

typedef char CommandCode;

const CommandCode IM_LOGGED = 0;
const CommandCode SERVER_DATA = 1;
const CommandCode LOGGIN_GAME = 2;
const CommandCode ERROR_MESSAGE = 3;
const CommandCode ADD_MAP_DATA = 4;
const CommandCode END_MAP_DATA = 5;
const CommandCode INITIALIZE_MAP = 6;
const CommandCode INITIALIZE_GRAPHICS = 7;
const CommandCode UPDATE_ENTITY = 8;

#endif /* COMMANDCODE_H_ */
