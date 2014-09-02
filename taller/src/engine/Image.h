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
	Image(const char* pFile, int r, int g, int b);
	Image(const char* pFile);

	virtual ~Image();

	void render(int xo, int yo, int dx, int dy);
	void render(int xo, int yo, int dx, int dy, float rotation);

	//Convierte SDL_Surface en SDL texture!
	static SDL_Texture *textureFromSurface(SDL_Surface *pSurface);

	SDL_Texture* getImageTexture();

	int getHeight();
	int getWidth();

	void setRotationPoint(int x, int y);

private:
	SDL_Surface *loadSurface(const char* pFile);
	SDL_Point* centerRotation;
	void completeRender(SDL_Rect *imageData, float angle,
			SDL_RendererFlip flip);

	int colorKeyR;
	int colorKeyG;
	int colorKeyB;

protected:
	Image();

	int height;
	int width;
	SDL_Texture* gImageTexture;
	SDL_Surface *gImage;

	virtual SDL_Rect * getImagePortion();

};

#endif /* IMAGE_H_ */
