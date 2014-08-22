/*
 * Image.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Image.h"

#include "SDL.h"

Image::Image(const char* pFile) {
	this->gImage = SDL_LoadBMP(pFile);
}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

