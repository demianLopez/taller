/**
 message_command.h

 Copyright 2014 Gaston Martinez Gaston.martinez.90@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses
 */

#ifndef MESSAGE_COMMAND_H_
#define MESSAGE_COMMAND_H_

typedef char command_id_type_t;
typedef char command_len_type_t;
typedef char* command_args_type_t;

//Comandos

#define SHOW_DEBUG_STRING 0

typedef struct _command {
	command_id_type_t command;
	command_len_type_t args_len;
	command_args_type_t command_args;
} message_command_t;

#endif /* MESSAGE_COMMAND_H_ */
