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
	/* Crea un nuevo mensaje. */
	Message();
	/* Crea un nuevo mensaje y le copia data. */
	Message(char * data, char size);

	/* Asigna un codigo de comando al mensaje.*/
	void addCommandCode(CommandCode commandCode);
	/* Agrega un char al mensaje. */
	void addChar(char c);
	/* Agrega una cantidad de chars al mensaje. Al final de lo copiado
	 * pone un \0. */
	void addCharArray(const char * array, char length);
	/* Agrega un float al final del mensaje. */
	void addFloat(float * f);

	/* Lee el codigo de comando.
	 * Se debe estar posicionado en el lugar donde esta guardado
	 * el mismo.
	 * Aumenta el indice de lectura. */
	CommandCode getCommandCode();
	/* Lee un array de chars.
	 * Aumenta el indice de lectura. */
	char getCharArray(char ** array);
	/* Lee un char.
	 * Aumenta el indice de lectura. */
	char getChar();
	/* Lee un float.
	 * Aumenta el indice de lectura. */
	float getFloat();

	/* Agrega un caracter END_CHAR al final del mensaje. */
	void addEndChar();


	virtual ~Message();

	/* Devuelve el mensaje entero.
	 * Asigna la longitud al primer lugar antes de hacerlo. */
	char * getMessageData();
	/* Devuelve la longitud del mensaje. */
	int getMessageLength();
	/* Devuelve el espacio disponible para seguir escribiendo. */
	char getSpace();
private:
	char * message;
	char pointer;
	char read;
};

#endif /* MESSAGE_H_ */
