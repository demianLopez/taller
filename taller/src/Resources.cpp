/*
 * Resources.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "Resources.h"
#include "engine/Image.h"
#include "engine/Animation.h"
#include "engine/SpriteSheet.h"

static const char * PLAYER_ANIM_PATH = "Resources/mainChar.png";

Resources::Resources() {
	this->backgroundImage = NULL;
	this->characterSpriteSheet = NULL;
	this->characterAnimationLeft = NULL;
	this->characterAnimationRight = NULL;
}

void Resources::loadBackground(const char *bPath){
	this->backgroundImage = new Image(bPath);
}

Animation * Resources::getPlayerAnimationLeft() {
	return this->characterAnimationLeft;
}

Animation * Resources::getPlayerAnimationRight(){
	return this->characterAnimationRight;
}

void Resources::loadAnimations(){
	this->characterSpriteSheet = new SpriteSheet(PLAYER_ANIM_PATH, 70, 80);
	this->characterAnimationLeft = new Animation();
	this->characterAnimationRight = new Animation();

	this->characterAnimationLeft->addFrame(this->characterSpriteSheet->getSubImage(0,0), 75);
	this->characterAnimationLeft->addFrame(this->characterSpriteSheet->getSubImage(1,0), 75);
	this->characterAnimationLeft->addFrame(this->characterSpriteSheet->getSubImage(2,0), 75);
	this->characterAnimationLeft->addFrame(this->characterSpriteSheet->getSubImage(3,0), 75);

	this->characterAnimationRight->addFrame(this->characterSpriteSheet->getSubImage(0,1), 75);
	this->characterAnimationRight->addFrame(this->characterSpriteSheet->getSubImage(1,1), 75);
	this->characterAnimationRight->addFrame(this->characterSpriteSheet->getSubImage(2,1), 75);
	this->characterAnimationRight->addFrame(this->characterSpriteSheet->getSubImage(3,1), 75);
}

Image * Resources::getBackground(){
	return this->backgroundImage;
}

Resources::~Resources() {
	if(this->backgroundImage != NULL){
		delete backgroundImage;
	}

	delete this->characterAnimationLeft;
	delete this->characterAnimationRight;
	delete this->characterSpriteSheet;
}

