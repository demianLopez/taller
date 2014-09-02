/*
 * Animation.cpp
 *
 *  Created on: 30/8/2014
 *      Author: EscDemi
 */

#include "Animation.h"
#include "AnimationFrame.h"
#include "Image.h"

Animation::Animation() {
	this->drawed = false;
	this->lastTimeDrawed = 0;
	this->lastDrawedFrame = 0;
}

AnimationFrame * Animation::getFrame(int index) {
	return this->frameList[index];
}

AnimationFrame * Animation::getCurrentFrame() {

	unsigned int currentTime = SDL_GetTicks();
	unsigned int lastTimeDrawed = 0;

	if (this->drawed) {
		lastTimeDrawed = this->lastTimeDrawed;
	} else {
		this->drawed = true;
		this->lastDrawedFrame = 0;
		this->lastTimeDrawed = currentTime;
		return this->frameList[0];
	}

	bool findFrame = false;
	int currentFrame = this->lastDrawedFrame;

	while (!findFrame) {
		AnimationFrame * frame = this->frameList[currentFrame];

		if ((lastTimeDrawed + frame->getFrameTime()) > currentTime) {
			findFrame = true;
		} else {
			currentFrame++;
			lastTimeDrawed += frame->getFrameTime();
			this->lastTimeDrawed += frame->getFrameTime();
			currentFrame = currentFrame % this->frameList.size();
		}
	}

	this->lastDrawedFrame = currentFrame;
	return this->frameList[currentFrame];
}

void Animation::addFrame(Image * frameImage, int frameTime) {
	AnimationFrame *animationFrame = new AnimationFrame(frameImage, frameTime);
	this->frameList.push_back(animationFrame);
}

int Animation::getFrameCount() {
	return this->frameList.size();
}

Animation::~Animation() {
	this->frameList.clear();
}

