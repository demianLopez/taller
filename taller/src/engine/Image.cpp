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
}

SDL_Texture* Image::getTexture(){
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

Image::~Image() {
	SDL_DestroyTexture(this->gImageTexture);
	SDL_FreeSurface(this->gImage);
}

