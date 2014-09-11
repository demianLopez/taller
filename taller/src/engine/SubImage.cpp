/*
 * SubImage.cpp
 *
 *  Created on: 29/8/2014
 *      Author: EscDemi
 */

#include "SubImage.h"

SubImage::SubImage(Image * originalImage, int width, int height, int xSprite, int ySprite) : Image() {

	this->gImageTexture = originalImage->getImageTexture();

	this->height = height;
	this->width = width;

	this->portionImage =  {xSprite * width, ySprite * height, width, height};
}

SubImage::~SubImage(){
	this->gImageTexture = NULL;
	this->gImage = NULL;
}

SDL_Rect * SubImage::getImagePortion(){
	return &portionImage;
}




