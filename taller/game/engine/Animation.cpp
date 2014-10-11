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
	this->drawOneTime = false;
	this->cicleFinish = false;
}

AnimationFrame * Animation::getFrame(int index){
	return this->frameList[index];
}

void Animation::setOneDraw(){
	this->drawOneTime = true;
}

void Animation::setFinished(bool finished){
	this->cicleFinish = finished;
}

bool Animation::isFinished(){
	return this->cicleFinish;
}

void Animation::reset(){
	this->drawed = false;
	this->lastTimeDrawed = 0;
	this->lastDrawedFrame = 0;
	this->cicleFinish = false;
}

AnimationFrame * Animation::getCurrentFrame(){

	unsigned int currentTime = SDL_GetTicks();
	unsigned int lastTimeDrawed = 0;

	if(this->drawed){
		lastTimeDrawed = this->lastTimeDrawed;
	} else {
		this->drawed = true;
		this->lastDrawedFrame = 0;
		this->lastTimeDrawed = currentTime;
		return this->frameList[0];
	}

	bool findFrame = false;
	int currentFrame = this->lastDrawedFrame;

	while(!findFrame){
		AnimationFrame * frame = this->frameList[currentFrame];

		if((lastTimeDrawed + frame->getFrameTime())>currentTime){
			findFrame = true;
		} else {
			currentFrame++;
			lastTimeDrawed += frame->getFrameTime();
			this->lastTimeDrawed += frame->getFrameTime();
			if((currentFrame / this->frameList.size()) >= 1 && this->drawOneTime) {
				this->cicleFinish = true;
			}
			currentFrame = currentFrame % this->frameList.size();
		}
	}

	this->lastDrawedFrame = currentFrame;
	return this->frameList[currentFrame];
}

void Animation::addFrame(Image * frameImage, int frameTime){
	AnimationFrame *animationFrame = new AnimationFrame(frameImage, frameTime);
	this->frameList.push_back(animationFrame);
}

int Animation::getFrameCount(){
	return this->frameList.size();
}

Animation::~Animation() {
	for(auto *frame : this->frameList){
		delete frame;
	}

	this->frameList.clear();
}

