/*
 * SpriteSheet.h
 *
 *  Created on: 29/8/2014
 *      Author: EscDemi
 */

#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include "Image.h"
class SubImage;

class SpriteSheet {
public:
	SpriteSheet(const char* pFile, int pX, int pY);

	Image * getSubImage(int x, int y);

	int getHorizontalCount();
	int getVerticalCount();

	int getHeight();
	int getWidth();

	Image * getSpriteSheetImage();

	virtual ~SpriteSheet();
private:
	Image *spriteImage;
	int pX;
	int pY;
	int verticalCount;
	int horizontalCount;
};

#endif /* SPRITESHEET_H_ */
