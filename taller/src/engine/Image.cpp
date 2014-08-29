/*
 * Image.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Image.h"

Image::Image(const char* pFile) {
	this->gImage = this->loadSurface(pFile);
	this->gImageTexture = Image::textureFromSurface(this->gImage);

	this->height = gImage->h;
	this->width = gImage->w;
}

Image::Image(){
	this->gImage = NULL;
	this->gImageTexture = NULL;

	this->height = 0;
	this->width = 0;
}

void Image::render(int xo, int yo, int dx, int dy){
	SDL_Rect imageData = {xo, yo, dx, dy};
	SDL_RenderCopy(GameElements::gRenderer, this->gImageTexture, NULL, &imageData);
}

SDL_Texture* Image::getImageTexture(){
	return this->gImageTexture;
}

SDL_Texture* Image::textureFromSurface(SDL_Surface* pSurface){
	SDL_Texture* newTexture;

	newTexture = SDL_CreateTextureFromSurface( GameElements::gRenderer, pSurface );

	if( newTexture == NULL ){
		printf( "Unable to convert texture from SDL Error: %s\n", SDL_GetError() );
	}

	return newTexture;
}

SDL_Surface* Image::loadSurface(const char *pFile)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(pFile);

    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", pFile, IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, GameElements::gScreenSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", pFile, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

int Image::getHeight(){
	return this->height;
}

int Image::getWidth(){
	return this->width;
}

Image::~Image() {
	SDL_DestroyTexture(this->gImageTexture);
	SDL_FreeSurface(this->gImage);
}

