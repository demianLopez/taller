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

void SubImage::render(int xo, int yo, int dx, int dy){
	SDL_Rect imageData = {xo, yo, dx, dy};
	SDL_RenderCopy(GameElements::gRenderer, this->gImageTexture, &this->portionImage, &imageData);
}


