/*
 * Graphics.cpp
 *
 *  Created on: 23/8/2014
 *      Author: EscDemi
 */

#include "Graphics.h"
#include "Image.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "SdlGfx/SDL2_gfxPrimitives.h"

Graphics::Graphics(TTF_Font * font) {
	this->currentFont = font;
	this->dAtCenter = false;
}

void Graphics::clearRenderObject(){
	SDL_RenderClear(GameElements::gRenderer);
}

void Graphics::setRendererObject(Image *image){
	if(image == NULL){
		SDL_SetRenderTarget(GameElements::gRenderer, NULL);
	} else {
		SDL_SetRenderTarget(GameElements::gRenderer, image->getImageTexture());
	}
}

void Graphics::drawImage(Image * image, int xo, int yo, int txo, int tyo, int tdx, int tdy, int dx, int dy){
	image->render(xo, yo, txo, tyo, tdx, tdy, dx, dy);
}

void Graphics::drawImage(Image *image){
	this->drawImage(image, 0, 0);
}


void Graphics::drawAtCenter(bool dAtCenter){
	this->dAtCenter = dAtCenter;
}

void Graphics::drawText(int x, int y, const char * text){
	SDL_Color textColor = { 255, 255, 255, 255 };


	SDL_Surface* textSurface = TTF_RenderText_Solid(currentFont, text, textColor );
	SDL_Texture* textTexture = Image::textureFromSurface(textSurface);

	SDL_Rect textData = {x, y, textSurface->w, textSurface->h};
	SDL_RenderCopy(GameElements::gRenderer, textTexture, NULL, &textData);


	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void Graphics::resetGraphics(){
	this->dAtCenter = false;
	SDL_SetRenderTarget(GameElements::gRenderer, NULL);
}

void Graphics::drawImage(Image *image, int xo, int yo, float rotation){
	this->drawImage(image, xo, yo, image->getWidth(), image->getHeight(), rotation);
}

void Graphics::drawImage(Image *image, int xo, int yo){
	this->drawImage(image, xo, yo, image->getWidth(), image->getHeight(), 0);
}

void Graphics::drawImage(Image *image, int xo, int yo, int dx, int dy, float rotation){
	int xOf = xo;
	int yOf = yo;
	if(this->dAtCenter){
		xOf = xo - dx/2;
		yOf = yo - dy/2;
	}
	image->render(xOf, yOf, dx, dy, rotation);
}

void Graphics::drawImage(Image *image, int xo, int yo, int dx, int dy){
	this->drawImage(image, xo, yo, dx, dy, 0);
}

void Graphics::drawAnimation(Animation * animation, int xo, int yo, float rotation){
	if(animation == NULL){
		return;
	}
	Image * animationImage = animation->getCurrentFrame()->getFrameImage();
	this->drawImage(animationImage, xo, yo, rotation);
}

void Graphics::drawAnimation(Animation * animation, int xo, int yo, int dx, int dy){
	this->drawAnimation(animation, xo, yo, dx, dy, 0);
}

void Graphics::drawAnimation(Animation * animation, int xo, int yo){
	if(animation == NULL){
		return;
	}
	Image * animationImage = animation->getCurrentFrame()->getFrameImage();
	this->drawImage(animationImage, xo, yo);
}

void Graphics::drawAnimation(Animation * animation, int xo, int yo, int dx, int dy, float rotation){
	if(animation == NULL){
		return;
	}
	Image * animationImage = animation->getCurrentFrame()->getFrameImage();
	this->drawImage(animationImage, xo, yo, dx, dy, rotation);
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

void Graphics::drawFillCircle(int x, int y, int rad, int r, int g, int b){
	filledCircleRGBA(GameElements::gRenderer, x, y, rad, r, g, b, 255);
}

void Graphics::setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha){
	SDL_SetRenderDrawColor(GameElements::gRenderer, red, green, blue, alpha);
}

void Graphics::drawFillPolygon(short int* vx, short int* vy, int n, int r, int g, int b){
	filledPolygonRGBA(GameElements::gRenderer, vx, vy, n, r, g, b, 255);
}

Graphics::~Graphics() {
	// TODO Auto-generated destructor stub
}

