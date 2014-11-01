/*
 * Message.h
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "CommandCode.h"

class Message {
public:
	Message();
	Message(char * data, char size);

	void addCommandCode(CommandCode commandCode);
	void addChar(char c);
	void addCharArray(const char * array, char length);

	CommandCode getCommandCode();
	char getCharArray(char ** array);
	char getChar();


	virtual ~Message();

	char * getMessageData();
	int getMessageLength();
private:
	char * message;
	char pointer;
	char read;
};

#endif /* MESSAGE_H_ */
