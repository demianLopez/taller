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
	SDL_RenderCopy(GameElements::gRenderer, image->getTexture(), NULL, NULL );
}

Graphics::~Graphics() {
	// TODO Auto-generated destructor stub
}

