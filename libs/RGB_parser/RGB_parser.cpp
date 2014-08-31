/**
 RGB_parser.cpp

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
#include "RGB_parser.h"

using std::tuple;
using std::make_tuple;
using std::string;

tuple<int, int, int> RGB_Parser::decode(string &encoded) {
	int red = -1;
	int green = -1;
	int blue = -1;

	if (encoded.size() != 6) {
		return make_tuple(red, green, blue);
	}

	string red_string = encoded.substr(0, 2);
	string green_string = encoded.substr(2, 2);
	string blue_string = encoded.substr(4, 2);

	red = decode_base_16(red_string);
	green = decode_base_16(green_string);
	blue = decode_base_16(blue_string);

	return make_tuple(red, green, blue);
}

int RGB_Parser::decode_base_16(std::string& encoded) {
	unsigned char x = encoded[0];
	unsigned char y = encoded[1];

	unsigned char x_decoded;
	unsigned char y_decoded;

	if (x < 48 || y < 48) //Antes de los numeros
		return -1;
	if (x > 70 || y > 70) //Despues de las letras validas
		return -1;
	if (x > 57 && x < 65) //X no es un numero ni una letra
		return -1;
	if (y > 57 && y < 65) //X no es un numero ni una letra
		return -1;

	if (x < 65) //Es numero
		x_decoded = x - 48;
	else
		x_decoded = 10 + (x - 65);

	if (y < 65) //Es numero
		y_decoded = y - 48;
	else
		y_decoded = 10 + (y - 65);

	x_decoded = x_decoded << 4;

	return x_decoded + y_decoded;
}
