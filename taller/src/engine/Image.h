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

	virtual void render(int xo, int yo, int dx, int dy);
	//Convierte SDL_Surface en SDL texture!
	static SDL_Texture *textureFromSurface(SDL_Surface *pSurface);

	SDL_Texture* getImageTexture();

	int getHeight();
	int getWidth();
private:
	SDL_Surface *loadSurface(const char* pFile);
protected:
	Image();

	int height;
	int width;
	SDL_Texture* gImageTexture;
	SDL_Surface *gImage;
};



#endif /* IMAGE_H_ */
