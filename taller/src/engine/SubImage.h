/*
 * SubImage.h
 *
 *  Created on: 29/8/2014
 *      Author: EscDemi
 */

#ifndef SUBIMAGE_H_
#define SUBIMAGE_H_

#include "Image.h"

class SubImage: public Image {
public:
	SubImage(Image *originalImage, int width, int height, int xSprite, int ySprite);
	void render(int xo, int yo, int dx, int dy);
private:
	SDL_Rect portionImage;
};

#endif /* SUBIMAGE_H_ */
