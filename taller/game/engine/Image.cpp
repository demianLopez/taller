/*
 * Image.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Image.h"
#include <stdio.h>

Image::Image(const char* pFile) {
	this->gImage = this->loadSurface(pFile);
	this->gImageTexture = IMG_LoadTexture(GameElements::gRenderer, pFile);

	this->height = gImage->h;
	this->width = gImage->w;

	this->centerRotation = NULL;
}

Image::Image(int width, int height) {
	this->gImage = NULL;
	this->gImageTexture = SDL_CreateTexture(GameElements::gRenderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(this->gImageTexture, SDL_BLENDMODE_BLEND);

	this->height = height;
	this->width = width;

	this->centerRotation = NULL;
}

Image::Image() {
	this->gImage = NULL;
	this->gImageTexture = NULL;

	this->height = 0;
	this->width = 0;

	this->centerRotation = NULL;
}

int Image::setAlpha(unsigned char alpha) {
	return SDL_SetTextureAlphaMod(this->gImageTexture, alpha);
}

void Image::render(int xo, int yo, int dx, int dy) {
	this->render(xo, yo, dx, dy, 0);
}

void Image::render(int xo, int yo, int txo, int tyo, int tdx, int tdy, int dx,
		int dy) {
	SDL_Rect imageData = { xo, yo, dx, dy };
	SDL_Rect imagePortion = { txo, tyo, tdx, tdy };
	SDL_RenderCopyEx(GameElements::gRenderer, this->gImageTexture,
			&imagePortion, &imageData, 0, this->centerRotation, SDL_FLIP_NONE);
}

void Image::render(int xo, int yo, int dx, int dy, float rotation) {
	SDL_Rect imageData = { xo, yo, dx, dy };
	this->completeRender(&imageData, rotation, SDL_FLIP_NONE);
}

void Image::completeRender(SDL_Rect *imageData, float angle,
		SDL_RendererFlip flip) {
	SDL_RenderCopyEx(GameElements::gRenderer, this->gImageTexture,
			this->getImagePortion(), imageData, angle, this->centerRotation,
			flip);
}

SDL_Rect * Image::getImagePortion() {
	return NULL;
}

SDL_Texture* Image::getImageTexture() {
	return this->gImageTexture;
}

SDL_Texture* Image::textureFromSurface(SDL_Surface* pSurface) {
	SDL_Texture* newTexture;

	newTexture = SDL_CreateTextureFromSurface(GameElements::gRenderer,
			pSurface);

	if (newTexture == NULL) {
		printf("Unable to convert texture from SDL Error: %s\n",
				SDL_GetError());
	}

	return newTexture;
}

SDL_Surface* Image::loadSurface(const char *pFile) {
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(pFile);

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", pFile,
		IMG_GetError());
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface,
				GameElements::gScreenSurface->format, NULL);
		if (optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", pFile,
					SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int Image::getHeight() {
	return this->height;
}

int Image::getWidth() {
	return this->width;
}

Image::~Image() {
	if (this->gImage != NULL) {
		SDL_FreeSurface(this->gImage);
	}

	if (this->gImageTexture != NULL) {
		SDL_DestroyTexture(this->gImageTexture);
	}

}

