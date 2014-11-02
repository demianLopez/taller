/*
 * CommandCode.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef COMMANDCODE_H_
#define COMMANDCODE_H_

typedef char CommandCode;
typedef char KeyCode;

const CommandCode IM_LOGGED = 0;
const CommandCode SERVER_DATA = 1;
const CommandCode LOGGIN_GAME = 2;
const CommandCode ERROR_MESSAGE = 3;
const CommandCode ADD_MAP_DATA = 4;
const CommandCode END_MAP_DATA = 5;
const CommandCode INITIALIZE_MAP = 6;
const CommandCode INITIALIZE_GRAPHICS = 7;
const CommandCode UPDATE_ENTITY = 8;
const CommandCode END_CHAR = 9;
const CommandCode UPDATE_PLAYER_ENTITY = 10;
const CommandCode ADD_PLAYER_DATA = 11;
const CommandCode KEY_EVENT = 12;

const KeyCode MOVE_LEFT = 0;
const KeyCode MOVE_RIGHT = 1;
const KeyCode JUMP = 2;
const KeyCode NOTHING = 3;

#endif /* COMMANDCODE_H_ */
