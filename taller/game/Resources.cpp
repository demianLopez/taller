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
static const char * PLAYER_ANIM_BW_PATH = "Resources/mainCharBW.png";
static const char * PLAYER_WALK_BW_PATH = "Resources/mainCharWalkBW.png";
static const char * PLAYER_JUMP_BW_PATH = "Resources/mainCharJumpBW.png";
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

Animation * Resources::getAnimationByAnimationCode(AnimationCode animationCode, bool offline){
	if(!offline){
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
	}else{
		switch(animationCode){
			case A_STAND_RIGHT:
				return this->characterStaticRightBW;
			case A_STAND_LEFT:
				return this->characterStaticLeftBW;
			case A_WALK_RIGHT:
				return this->characterStaticRightBW;
				break;
			case A_WALK_LEFT:
				return this->characterStaticLeftBW;
				break;
			case A_JUMP_RIGHT:
				return this->characterAirRightBW;
			case A_JUMP_LEFT:
				return this->characterAirLeftBW;
		}
	}
	return NULL; //Si llego aca algo esta mal
}

void Resources::loadColoredAnimations(){
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
}

void Resources::loadBWAnimations(){
	this->characterSpriteSheetBW = new SpriteSheet(PLAYER_ANIM_BW_PATH, 70, 80);
	this->characterAnimationLeftBW = new Animation();
	this->characterAnimationRightBW = new Animation();

	this->characterAnimationLeftBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(0, 0), 75);
	this->characterAnimationLeftBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(1, 0), 75);
	this->characterAnimationLeftBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(2, 0), 75);
	this->characterAnimationLeftBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(3, 0), 75);

	this->characterAnimationRightBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(0, 1), 75);
	this->characterAnimationRightBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(1, 1), 75);
	this->characterAnimationRightBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(2, 1), 75);
	this->characterAnimationRightBW->addFrame(
			this->characterSpriteSheetBW->getSubImage(3, 1), 75);

	this->characterWalkBW = new SpriteSheet(PLAYER_WALK_BW_PATH, 46, 78);
	this->characterWalkRightBW = new Animation();
	this->characterWalkLeftBW = new Animation();

	this->characterWalkRightBW->addFrame(this->characterWalkBW->getSubImage(0, 1),
			75);
	this->characterWalkRightBW->addFrame(this->characterWalkBW->getSubImage(1, 1),
			75);
	this->characterWalkRightBW->addFrame(this->characterWalkBW->getSubImage(2, 1),
			75);
	this->characterWalkRightBW->addFrame(this->characterWalkBW->getSubImage(3, 1),
			75);

	this->characterWalkLeftBW->addFrame(this->characterWalkBW->getSubImage(0, 0),
			75);
	this->characterWalkLeftBW->addFrame(this->characterWalkBW->getSubImage(1, 0),
			75);
	this->characterWalkLeftBW->addFrame(this->characterWalkBW->getSubImage(2, 0),
			75);
	this->characterWalkLeftBW->addFrame(this->characterWalkBW->getSubImage(3, 0),
			75);

	this->characterJumpBW = new SpriteSheet(PLAYER_JUMP_BW_PATH, 55, 83);

	this->characterStaticLeftBW = new Animation();
	this->characterStaticRightBW = new Animation();

	this->characterAirLeftBW = new Animation();
	this->characterAirRightBW = new Animation();

	this->topJumpLeftBW = new Animation();
	this->topJumpRightBW = new Animation();

	this->characterStaticLeftBW->addFrame(this->characterJumpBW->getSubImage(1, 0),
			1000);
	this->characterStaticRightBW->addFrame(this->characterJumpBW->getSubImage(6, 1),
			1000);

	this->characterAirLeftBW->addFrame(this->characterJumpBW->getSubImage(0, 0),
			1000);
	this->characterAirRightBW->addFrame(this->characterJumpBW->getSubImage(7, 1),
			1000);

	this->topJumpLeftBW->addFrame(this->characterJumpBW->getSubImage(3, 0), 75);
	this->topJumpLeftBW->addFrame(this->characterJumpBW->getSubImage(4, 0), 75);
	this->topJumpLeftBW->addFrame(this->characterJumpBW->getSubImage(5, 0), 75);
	this->topJumpLeftBW->addFrame(this->characterJumpBW->getSubImage(6, 0), 75);
	this->topJumpLeftBW->addFrame(this->characterJumpBW->getSubImage(7, 0), 75);

	this->topJumpRightBW->addFrame(this->characterJumpBW->getSubImage(4, 1), 50);
	this->topJumpRightBW->addFrame(this->characterJumpBW->getSubImage(3, 1), 50);
	this->topJumpRightBW->addFrame(this->characterJumpBW->getSubImage(2, 1), 50);
	this->topJumpRightBW->addFrame(this->characterJumpBW->getSubImage(1, 1), 50);
	this->topJumpRightBW->addFrame(this->characterJumpBW->getSubImage(0, 1), 50);
}

void Resources::loadAnimations() {
	//Animaciones del pj en color y en B&W
	loadColoredAnimations();
	loadBWAnimations();

	this->emoticons = new SpriteSheet(EMOTICONS_PATH, 32, 32);

	this->sleepingEmoticon = new Animation();
	this->heartAnimation = new Animation();
	this->exclamationAnimation = new Animation();

	for(int i = 0; i < 8; i++){
		sleepingEmoticon->addFrame(emoticons->getSubImage(i, 9), 150);
		if( i != 0){
			heartAnimation->addFrame(emoticons->getSubImage(i, 3), 150);
			exclamationAnimation->addFrame(emoticons->getSubImage(i, 0), 150);
		}
	}

	for(int i = 7; i > 0; i--) {
		heartAnimation->addFrame(emoticons->getSubImage(i, 3), 150);
		exclamationAnimation->addFrame(emoticons->getSubImage(i, 0), 150);
	}

	this->nameFonts = TTF_OpenFont("Resources/font.ttf", 18);

}

Animation * Resources::getExclamationAnimation(){
	return this->exclamationAnimation;
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

Animation * Resources::getHeartAnimation(){
	return this->heartAnimation;
}

Resources::~Resources() {
	if (this->backgroundImage != NULL) {
		delete backgroundImage;
	}

	/* Animaciones pj */
	//Color
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
	//B&N
	delete this->characterAnimationLeftBW;
	delete this->characterAnimationRightBW;
	delete this->characterSpriteSheetBW;

	delete this->characterWalkLeftBW;
	delete this->characterWalkRightBW;

	delete this->characterWalkBW;

	delete this->characterStaticLeftBW;
	delete this->characterStaticRightBW;
	delete this->characterAirLeftBW;
	delete this->characterAirRightBW;

	delete this->topJumpLeftBW;
	delete this->topJumpRightBW;

	delete this->characterJumpBW;
	/* Fin animaciones pj */

	delete this->sleepingEmoticon;
	delete this->exclamationAnimation;
	delete this->heartAnimation;
	delete this->emoticons;
	TTF_CloseFont(nameFonts);

}

