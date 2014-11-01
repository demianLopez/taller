/*
 * Message.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include <Message.h>
#include <cstring>

Message::Message() {
	this->message = new char[256];
	pointer = 0;
	read = 0;
}

Message::Message(char *data, char size) {
	this->message = new char[256];
	memcpy(message, data, size - 1);
	this->pointer = size - 1;
	read = 0;
}

void Message::addChar(char c){
	message[pointer] = c;
	pointer++;
}

void Message::addCharArray(char * array, char length){
	this->addChar(length);
	memcpy(&message[pointer], array, length);
	pointer += length;
}

void Message::addCommandCode(CommandCode commandCode){
	message[pointer] = commandCode;
	pointer++;
}

CommandCode Message::getCommandCode(){
	char cD = message[read];
	read ++;
	return cD;
}

char Message::getChar(){
	char a = message[read];
	read ++;
	return a;
}

char Message::getCharArray(char ** array){
	char size = this->getChar();
	*array = new char[size];
	memcpy(*array, &message[read], size);
	read += size;
	return size;
}

char * Message::getMessageData(){
	message[pointer] = '\0';
	return this->message;
}

int Message::getMessageLength(){
	return pointer + 1;
}

Message::~Message() {
	delete[] this->message;
}

