/*
 * message_command.h
 *
 *  Created on: 25/10/2014
 *      Author: hige
 */

#ifndef MESSAGE_COMMAND_H_
#define MESSAGE_COMMAND_H_

typedef char  command_id_type_t;
typedef char  command_len_type_t;
typedef char* command_args_type_t;

//Comandos

#define SHOW_DEBUG_STRING 0

typedef struct _command{
	command_id_type_t	command;
	command_len_type_t	args_len;
	command_args_type_t	command_args;
} message_command_t;


#endif /* MESSAGE_COMMAND_H_ */
