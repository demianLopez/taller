/**
 logger_test.cpp

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

#include "libs/logger/logger.h"

int main()
{
	Logger::initialize_log("a.log");

	Logger::log("a.log","Main.c",Logger::INFO,"Esto arranco bien");
	Logger::log("a.log","Main.c",Logger::ERROR,"Esto no estaria funcionando");
	Logger::log("a.log","Main.c",Logger::WARNING,"Esto se rompio");

	return 0;
}
