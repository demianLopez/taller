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
typedef char AnimationCode;
typedef char EntityType;

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
const CommandCode UPDATE_TIMING = 13;
const CommandCode LOCK_CAMERA_ENTITY = 14;
const CommandCode REQUEST_KEY_DATA = 15;
const CommandCode CLOSING_GAME = 16;
const CommandCode SHOW_MESSAGE = 17;
const CommandCode IM_ALIVE = 18;
const CommandCode UPDATE_PLAYER_STAT = 19;
const CommandCode START_GAME = 20;
const CommandCode END_LEVEL = 21;

const KeyCode MOVE_LEFT_DOWN = 0;
const KeyCode MOVE_RIGHT_DOWN = 1;
const KeyCode JUMP = 2;
const KeyCode NOTHING = 3;
const KeyCode MOVE_LEFT_UP = 4;
const KeyCode MOVE_RIGHT_UP = 5;

const AnimationCode A_STAND_RIGHT = 0;
const AnimationCode A_STAND_LEFT = 1;
const AnimationCode A_WALK_RIGHT = 2;
const AnimationCode A_WALK_LEFT = 3;
const AnimationCode A_JUMP_RIGHT = 4;
const AnimationCode A_JUMP_LEFT = 5;

const EntityType P_SOLID = 0;
const EntityType P_RECTANGLE = 1;

#endif /* COMMANDCODE_H_ */
