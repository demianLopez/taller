/*
 * Image.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef IMAGE_H_
#define IMAGE_H_
#include "LibIncludes.h"
#include "GameElements.h"

#include <iostream>

class Image {
public:
	Image(const char* pFile);
	virtual ~Image();

	SDL_Texture* getTexture();


	//Convierte SDL_Surface en SDL texture!
	static SDL_Texture *textureFromSurface(SDL_Surface *pSurface);

	int getHeight();
	int getWidth();
private:
	SDL_Surface *loadSurface(const char* pFile);

	SDL_Texture* gImageTexture;
	SDL_Surface *gImage;
};



#endif /* IMAGE_H_ */
