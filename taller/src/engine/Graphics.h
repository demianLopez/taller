/*
 * Graphics.h
 *
 *  Created on: 23/8/2014
 *      Author: EscDemi
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "LibIncludes.h"
class Image;

class Graphics {

public:
	Graphics();
	virtual ~Graphics();
	void drawImage(Image *image);
private:

};

#endif /* GRAPHICS_H_ */
