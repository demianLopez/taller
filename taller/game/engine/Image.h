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
#include "Graphics.h"

#include <iostream>

class Image {
public:

	Image(const char* pFile);
	Image(int width, int height);

	virtual ~Image();

	void render(int xo, int yo, int dx, int dy);
	void render(int xo, int yo, int dx, int dy, float rotation);
	void render(int xo, int yo, int txo, int tyo, int dx, int dy);


	//Return 0 if succes, or negative error code on faliure!
	int setAlpha(unsigned char alpha);

	//Convierte SDL_Surface en SDL texture!
	static SDL_Texture *textureFromSurface(SDL_Surface *pSurface);

	SDL_Texture* getImageTexture();

	int getHeight();
	int getWidth();

	void setRotationPoint(int x, int y);
private:
	SDL_Surface *loadSurface(const char* pFile);
	SDL_Point* centerRotation;
	void completeRender(SDL_Rect *imageData, float angle, SDL_RendererFlip flip);

protected:
	Image();

	int height;
	int width;
	SDL_Texture* gImageTexture;
	SDL_Surface *gImage;

	virtual SDL_Rect * getImagePortion();

};



#endif /* IMAGE_H_ */
