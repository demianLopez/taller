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
	pointer = 1;
	read = 1;
}

Message::Message(char *data, char size) {
	this->message = new char[256];
	memcpy(message, data, size);
	this->pointer = size;
	read = 0;
}

void Message::addFloat(float * f) {
	memcpy(&message[pointer], f, sizeof(float));
	pointer += sizeof(float);
}

char Message::getSpace() {
	return 256 - this->getMessageLength();
}

void Message::addChar(char c) {
	message[pointer] = c;
	pointer++;
}

void Message::addCharArray(const char * array, char length) {
	this->addChar(length);
	memcpy(&message[pointer], array, length);
	pointer += length;
}

void Message::addCommandCode(CommandCode commandCode) {
	message[pointer] = commandCode;
	pointer++;
}

CommandCode Message::getCommandCode() {
	char cD = message[read];
	read++;
	return cD;
}

char Message::getChar() {
	char a = message[read];
	read++;
	return a;
}

float Message::getFloat() {
	float p;
	memcpy(&p, &message[read], sizeof(float));
	read += sizeof(float);
	return p;
}

char Message::getCharArray(char ** array) {
	char size = this->getChar();
	*array = new char[size];
	memcpy(*array, &message[read], size);
	read += size;
	return size;
}

char * Message::getMessageData() {
	//message[pointer] = '\0';
	message[0] = pointer - 1;
	return this->message;
}

int Message::getMessageLength() {
	return pointer;
}

Message::~Message() {
	delete[] this->message;
}

