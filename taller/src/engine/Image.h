/*
 * Image.h
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "SDL.h"

class Image {
public:
	Image(const char* pFile);
	virtual ~Image();
private:
	SDL_Surface *gImage;
};

#endif /* IMAGE_H_ */
