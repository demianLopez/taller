/*
 * AnimationFrame.h
 *
 *  Created on: 31/8/2014
 *      Author: EscDemi
 */

#ifndef ANIMATIONFRAME_H_
#define ANIMATIONFRAME_H_

class Image;

class AnimationFrame {
public:
	AnimationFrame(Image *frameImage, unsigned int frameTime);

	unsigned int getFrameTime();
	Image * getFrameImage();

	virtual ~AnimationFrame();

private:
	Image* frameImage;
	unsigned int frameTime;
};

#endif /* ANIMATIONFRAME_H_ */
