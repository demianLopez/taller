/*
 * AnimationFrame.cpp
 *
 *  Created on: 31/8/2014
 *      Author: EscDemi
 */

#include "AnimationFrame.h"
#include "Image.h"

AnimationFrame::AnimationFrame(Image *frameImage, unsigned int frameTime) {
	this->frameImage = frameImage;
	this->frameTime = frameTime;
}

unsigned int AnimationFrame::getFrameTime() {
	return this->frameTime;
}

Image* AnimationFrame::getFrameImage() {
	return this->frameImage;
}

AnimationFrame::~AnimationFrame() {
	delete frameImage;
}

