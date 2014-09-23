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
static const char * PLAYER_WALK_PATH = "Resources/mainCharWalk.png";
static const char * PLAYER_JUMP_PATH = "Resources/mainCharJump.png";

Resources::Resources() {
	this->backgroundImage = NULL;
	this->characterSpriteSheet = NULL;
	this->characterWalk = NULL;

	this->characterAnimationLeft = NULL;
	this->characterAnimationRight = NULL;
	this->characterWalkRight = NULL;
	this->characterWalkLeft = NULL;
	this->characterStaticLeft = NULL;
	this->characterStaticRight = NULL;

	this->characterJump = NULL;
	this->characterAirLeft = NULL;
	this->characterAirRight = NULL;
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

	this->characterWalk = new SpriteSheet(PLAYER_WALK_PATH, 46, 78);
	this->characterWalkRight = new Animation();
	this->characterWalkLeft = new Animation();

	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(0, 1), 75);
	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(1, 1), 75);
	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(2, 1), 75);
	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(3, 1), 75);

	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(0, 0), 75);
	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(1, 0), 75);
	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(2, 0), 75);
	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(3, 0), 75);

	this->characterJump = new SpriteSheet(PLAYER_JUMP_PATH, 55, 83);

	this->characterStaticLeft = new Animation();
	this->characterStaticRight = new Animation();

	this->characterAirLeft = new Animation();
	this->characterAirRight = new Animation();

	this->characterStaticLeft->addFrame(this->characterJump->getSubImage(1, 0), 1000);
	this->characterStaticRight->addFrame(this->characterJump->getSubImage(6, 1), 1000);

	this->characterAirLeft->addFrame(this->characterJump->getSubImage(0, 0), 1000);
	this->characterAirRight->addFrame(this->characterJump->getSubImage(7, 1), 1000);
}

Image * Resources::getBackground(){
	return this->backgroundImage;
}

Animation * Resources::getPlayerStaticLeft(){
	return this->characterStaticLeft;
}

Animation * Resources::getPlayerStaticRight(){
	return this->characterStaticRight;
}

Animation * Resources::getPlayerWalkLeft(){
	return this->characterWalkLeft;
}

Animation * Resources::getPlayerWalkRight(){
	return this->characterWalkRight;
}

Animation * Resources::getPlayerAirLeft(){
	return this->characterAirLeft;
}

Animation * Resources::getPlayerAirRight(){
	return this->characterAirRight;
}

Resources::~Resources() {
	if(this->backgroundImage != NULL){
		delete backgroundImage;
	}

	delete this->characterAnimationLeft;
	delete this->characterAnimationRight;
	delete this->characterSpriteSheet;

	delete this->characterWalkLeft;
	delete this->characterWalkRight;

	delete this->characterWalk;

	delete this->characterStaticLeft;
	delete this->characterStaticRight;
	delete this->characterAirLeft;
	delete this->characterAirRight;

	delete this->characterJump;


}

