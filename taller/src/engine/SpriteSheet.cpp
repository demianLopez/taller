/*
 * SpriteSheet.cpp
 *
 *  Created on: 29/8/2014
 *      Author: EscDemi
 */

#include "SpriteSheet.h"
#include "SubImage.h"

SpriteSheet::SpriteSheet(const char* pFile, int pX, int pY){
	this->spriteImage = new Image(pFile);
	this->pX = pX;
	this->pY = pY;

	this->horizontalCount = this->spriteImage->getWidth() / pX;
	this->verticalCount = this->spriteImage->getHeight() / pY;
}

Image * SpriteSheet::getSubImage(int x, int y){
	//Evitamos irnos fuera de la imagen
	int xSubImage = x % this->horizontalCount;
	int ySubImage = y % this->verticalCount;

	SubImage *subImage = new SubImage(this->spriteImage, this->pX, this->pY, xSubImage, ySubImage);

	return subImage;
}

Image * SpriteSheet::getSpriteSheetImage(){
	return spriteImage;
}

int SpriteSheet::getHeight(){
	return this->spriteImage->getHeight();
}

int SpriteSheet::getWidth(){
	return this->spriteImage->getWidth();
}

int SpriteSheet::getHorizontalCount(){
	return this->horizontalCount;
}

int SpriteSheet::getVerticalCount(){
	return this->verticalCount;
}

SpriteSheet::~SpriteSheet() {
	delete this->spriteImage;
}

