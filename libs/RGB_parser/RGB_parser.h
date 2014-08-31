/**
 RGB_parser.h

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
#ifndef RGB_PARSER_H_
#define RGB_PARSER_H_

#include <string>
#include <tuple>

class RGB_Parser {
public:
	static std::tuple<int, int, int> decode(std::string &encoded);

private:
	static int decode_base_16(std::string &encoded);
};

#endif /* RGB_PARSER_H_ */
