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
	~SubImage();
private:
	SDL_Rect portionImage;
protected:
	virtual SDL_Rect* getImagePortion();
};

#endif /* SUBIMAGE_H_ */
