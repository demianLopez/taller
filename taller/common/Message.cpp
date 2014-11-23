/*
 * Message.cpp
 *
 *  Created on: 31/10/2014
 *      Author: demian
 */

#include "Message.h"
#include <cstring>
#include <iostream>

/* Crea un nuevo mensaje. */
Message::Message() {
	this->message = new char[256];
	pointer = 1;
	read = 1;
}

CommandCode Message::getFirstCommandCode() {
	return message[0];
}

/* Crea un nuevo mensaje y le copia data. */
Message::Message(char *data, char size) {
	this->message = new char[256];
	memcpy(message, data, size);
	this->pointer = size;
	read = 0; //FIXME: Esta bien que aca este en cero pero en la anterior en 1?
}

/* Agrega un caracter END_CHAR al final del mensaje. */
void Message::addEndChar() {
	this->addChar(END_CHAR);
}

/* Agrega un float al final del mensaje. */
void Message::addFloat(float * f) {
	memcpy(&message[pointer], f, sizeof(float));
	pointer += sizeof(float);
}

/* Devuelve el espacio disponible para seguir escribiendo. */
char Message::getSpace() {
	return 256 - this->getMessageLength();
}

/* Agrega un char al mensaje. */
void Message::addChar(char c) {
	message[pointer] = c;
	pointer++;
}

/* Agrega una cantidad de chars al mensaje. Al final de lo copiado
 * pone un \0. */
void Message::addCharArray(const char * array, char length) {
	this->addChar(length + 1);
	memcpy(&message[pointer], array, length);
	pointer += length;
	this->addChar('\0');
}

/* Asigna un codigo de comando al mensaje.*/
void Message::addCommandCode(CommandCode commandCode) {
	message[pointer] = commandCode;
	pointer++;
}

void Message::addKeyEventCode(KeyCode keyCode) {
	message[pointer] = keyCode;
	pointer++;
}

void Message::addAnimationCode(AnimationCode animationCode) {
	message[pointer] = animationCode;
	pointer++;
}

/* Lee el codigo de comando.
 * Se debe estar posicionado en el lugar donde esta guardado
 * el mismo.
 * Aumenta el indice de lectura. */
CommandCode Message::getCommandCode() {
	char cD = message[read];
	read++;
	return cD;
}

AnimationCode Message::getAnimationCode() {
	char cD = message[read];
	read++;
	return cD;
}

KeyCode Message::getKeyCode() {
	char cD = message[read];
	read++;
	return cD;
}

/* Lee un char.
 * Aumenta el indice de lectura. */
char Message::getChar() {
	char a = message[read];
	read++;
	return a;
}

/* Lee un float.
 * Aumenta el indice de lectura. */
float Message::getFloat() {
	float p;
	memcpy(&p, &message[read], sizeof(float));
	read += sizeof(float);
	return p;
}

/* Lee un array de chars.
 * Aumenta el indice de lectura. */
char Message::getCharArray(char ** array) {
	char size = this->getChar();
	*array = new char[size + 1];
	memcpy(*array, &message[read], size);
	//*array[size -1] = 0;
	//std::cout<<(int) size<<"-"<<*array<<std::endl;
	read += size;
	return size;
}

/* Devuelve el mensaje entero.
 * Asigna la longitud al primer lugar antes de hacerlo. */
char * Message::getMessageData() {
	//message[pointer] = '\0';
	message[0] = pointer - 1;
	return this->message;
}

/* Devuelve la longitud del mensaje. */
int Message::getMessageLength() {
	return pointer;
}

Message::~Message() {
	delete[] this->message;
}

