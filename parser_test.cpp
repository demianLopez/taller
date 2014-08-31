/**
 parser_test.cpp

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

#include <iostream>
#include <tuple>

#include "libs/RGB_parser/RGB_parser.h"

int main() {

	std::string color0 = "010A0F";
	std::string color1 = "11AAFF";
	std::string color2 = "RRrr&&";
	std::string color3 = "Color3";
	std::string color4 = "FFFFFFF";
	std::string color5 = "00000";

	int red, green, blue;

	std::tie(red, green, blue) = RGB_Parser::decode(color0);
	std::cout << "(" << red << "," << green << "," << blue << ")" << std::endl;

	std::tie(red, green, blue) = RGB_Parser::decode(color1);
	std::cout << "(" << red << "," << green << "," << blue << ")" << std::endl;

	std::tie(red, green, blue) = RGB_Parser::decode(color2);
	std::cout << "(" << red << "," << green << "," << blue << ")" << std::endl;

	std::tie(red, green, blue) = RGB_Parser::decode(color3);
	std::cout << "(" << red << "," << green << "," << blue << ")" << std::endl;

	std::tie(red, green, blue) = RGB_Parser::decode(color4);
	std::cout << "(" << red << "," << green << "," << blue << ")" << std::endl;

	std::tie(red, green, blue) = RGB_Parser::decode(color5);
	std::cout << "(" << red << "," << green << "," << blue << ")" << std::endl;

	return 0;
}
