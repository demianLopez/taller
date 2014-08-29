/*
 * Graphics.cpp
 *
 *  Created on: 23/8/2014
 *      Author: EscDemi
 */

#include "Graphics.h"
#include "Image.h"

Graphics::Graphics() {

}

void Graphics::drawImage(Image *image){
	this->drawImage(image, 0, 0);
}

void Graphics::drawImage(Image *image, int xo, int yo, float rotation){
	this->drawImage(image, xo, yo, image->getWidth(), image->getHeight(), rotation);
}

void Graphics::drawImage(Image *image, int xo, int yo){
	this->drawImage(image, xo, yo, image->getWidth(), image->getHeight(), 0);
}

void Graphics::drawImage(Image *image, int xo, int yo, int dx, int dy, float rotation){
	image->render(xo, yo, dx, dy, rotation);
}

void Graphics::drawImage(Image *image, int xo, int yo, int dx, int dy){
	this->drawImage(image, xo, yo, dx, dy, 0);
}

void Graphics::drawFillRect(int xo, int yo, int dx, int dy){
    SDL_Rect fillRect = { xo, yo, dx, dy};
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect(GameElements::gRenderer, &fillRect );
}

void Graphics::drawRect(int xo, int yo, int dx, int dy){
    SDL_Rect outlineRect = { xo, yo, dx, dy };
    //SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect(GameElements::gRenderer, &outlineRect );
}

void Graphics::drawLine(int xo, int yo, int xf, int yf){
	SDL_RenderDrawLine(GameElements::gRenderer, xo, yo, xf, yf);
}

void Graphics::drawPoint(int x, int y){
	SDL_RenderDrawPoint(GameElements::gRenderer, x, y);
}

void Graphics::setColor(unsigned char red, unsigned char green, unsigned char blue){
	this->setColor(red, green, blue, 255);
}

void Graphics::setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha){
	SDL_SetRenderDrawColor(GameElements::gRenderer, red, green, blue, alpha);
}

Graphics::~Graphics() {
	// TODO Auto-generated destructor stub
}

