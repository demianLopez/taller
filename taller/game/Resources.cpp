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
static const char * EMOTICONS_PATH = "Resources/balloon-emoticons-go.png";

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
	this->topJumpLeft = NULL;
	this->topJumpRight = NULL;

	this->emoticons = NULL;
	this->sleepingEmoticon = NULL;
}

void Resources::loadBackground(const char *bPath) {
	this->backgroundImage = new Image(bPath);
}

Animation * Resources::getPlayerAnimationLeft() {
	return this->characterAnimationLeft;
}

Animation * Resources::getPlayerAnimationRight() {
	return this->characterAnimationRight;
}

Animation * Resources::getAnimationByAnimationCode(AnimationCode animationCode){

	switch(animationCode){
		case A_STAND_RIGHT:
			return this->characterStaticRight;
		case A_STAND_LEFT:
			return this->characterStaticLeft;
		case A_WALK_RIGHT:
			return this->characterWalkRight;
			break;
		case A_WALK_LEFT:
			return this->characterWalkLeft;
			break;
		case A_JUMP_RIGHT:
			return this->characterAirRight;
		case A_JUMP_LEFT:
			return this->characterAirLeft;
	}

}

void Resources::loadAnimations() {
	this->characterSpriteSheet = new SpriteSheet(PLAYER_ANIM_PATH, 70, 80);
	this->characterAnimationLeft = new Animation();
	this->characterAnimationRight = new Animation();

	this->characterAnimationLeft->addFrame(
			this->characterSpriteSheet->getSubImage(0, 0), 75);
	this->characterAnimationLeft->addFrame(
			this->characterSpriteSheet->getSubImage(1, 0), 75);
	this->characterAnimationLeft->addFrame(
			this->characterSpriteSheet->getSubImage(2, 0), 75);
	this->characterAnimationLeft->addFrame(
			this->characterSpriteSheet->getSubImage(3, 0), 75);

	this->characterAnimationRight->addFrame(
			this->characterSpriteSheet->getSubImage(0, 1), 75);
	this->characterAnimationRight->addFrame(
			this->characterSpriteSheet->getSubImage(1, 1), 75);
	this->characterAnimationRight->addFrame(
			this->characterSpriteSheet->getSubImage(2, 1), 75);
	this->characterAnimationRight->addFrame(
			this->characterSpriteSheet->getSubImage(3, 1), 75);

	this->characterWalk = new SpriteSheet(PLAYER_WALK_PATH, 46, 78);
	this->characterWalkRight = new Animation();
	this->characterWalkLeft = new Animation();

	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(0, 1),
			75);
	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(1, 1),
			75);
	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(2, 1),
			75);
	this->characterWalkRight->addFrame(this->characterWalk->getSubImage(3, 1),
			75);

	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(0, 0),
			75);
	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(1, 0),
			75);
	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(2, 0),
			75);
	this->characterWalkLeft->addFrame(this->characterWalk->getSubImage(3, 0),
			75);

	this->characterJump = new SpriteSheet(PLAYER_JUMP_PATH, 55, 83);

	this->characterStaticLeft = new Animation();
	this->characterStaticRight = new Animation();

	this->characterAirLeft = new Animation();
	this->characterAirRight = new Animation();

	this->topJumpLeft = new Animation();
	this->topJumpRight = new Animation();

	this->characterStaticLeft->addFrame(this->characterJump->getSubImage(1, 0),
			1000);
	this->characterStaticRight->addFrame(this->characterJump->getSubImage(6, 1),
			1000);

	this->characterAirLeft->addFrame(this->characterJump->getSubImage(0, 0),
			1000);
	this->characterAirRight->addFrame(this->characterJump->getSubImage(7, 1),
			1000);

	this->topJumpLeft->addFrame(this->characterJump->getSubImage(3, 0), 75);
	this->topJumpLeft->addFrame(this->characterJump->getSubImage(4, 0), 75);
	this->topJumpLeft->addFrame(this->characterJump->getSubImage(5, 0), 75);
	this->topJumpLeft->addFrame(this->characterJump->getSubImage(6, 0), 75);
	this->topJumpLeft->addFrame(this->characterJump->getSubImage(7, 0), 75);

	this->topJumpRight->addFrame(this->characterJump->getSubImage(4, 1), 50);
	this->topJumpRight->addFrame(this->characterJump->getSubImage(3, 1), 50);
	this->topJumpRight->addFrame(this->characterJump->getSubImage(2, 1), 50);
	this->topJumpRight->addFrame(this->characterJump->getSubImage(1, 1), 50);
	this->topJumpRight->addFrame(this->characterJump->getSubImage(0, 1), 50);

	this->emoticons = new SpriteSheet(EMOTICONS_PATH, 32, 32);

	this->sleepingEmoticon = new Animation();

	for(int i = 0; i < 8; i++){
		sleepingEmoticon->addFrame(emoticons->getSubImage(i, 9), 150);
	}

	this->nameFonts = TTF_OpenFont("Resources/font.ttf", 18);

}

Image * Resources::getBackground() {
	return this->backgroundImage;
}

Animation * Resources::getPlayerStaticLeft() {
	return this->characterStaticLeft;
}

Animation * Resources::getPlayerStaticRight() {
	return this->characterStaticRight;
}

Animation * Resources::getPlayerWalkLeft() {
	return this->characterWalkLeft;
}

Animation * Resources::getPlayerWalkRight() {
	return this->characterWalkRight;
}

Animation * Resources::getPlayerAirLeft() {
	return this->characterAirLeft;
}

Animation * Resources::getPlayerAirRight() {
	return this->characterAirRight;
}

Animation * Resources::getTopJumpLeft() {
	return this->topJumpLeft;
}

Animation * Resources::getTopJumpRight() {
	return this->topJumpRight;
}

Animation * Resources::getSleepingEmoticon(){
	return this->sleepingEmoticon;
}

TTF_Font * Resources::getNameFont(){
	return this->nameFonts;
}

Resources::~Resources() {
	if (this->backgroundImage != NULL) {
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

	delete this->topJumpLeft;
	delete this->topJumpRight;

	delete this->characterJump;

	delete this->sleepingEmoticon;
	delete this->emoticons;
	delete this->nameFonts;

}

