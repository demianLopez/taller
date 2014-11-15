/*
 * Resources.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

class Image;
class SpriteSheet;
class Animation;

#include "CommandCode.h"
#include "engine/LibIncludes.h"

class Resources {
public:
	Resources();

	void loadBackground(const char * bPath);
	void loadImage(const char * iPath);

	void loadAnimations();

	Animation * getPlayerAnimationLeft();
	Animation * getPlayerAnimationRight();
	Animation * getPlayerWalkLeft();
	Animation * getPlayerWalkRight();

	Animation * getPlayerStaticLeft();
	Animation * getPlayerStaticRight();

	Animation * getPlayerAirLeft();
	Animation * getPlayerAirRight();

	Animation * getTopJumpRight();
	Animation * getTopJumpLeft();

	Animation * getAnimationByAnimationCode(AnimationCode animationCode,
			bool offline = false);

	Animation * getSleepingEmoticon();
	Animation * getExclamationAnimation();

	Image * getBackground();

	TTF_Font * getNameFont();

	Animation * getHeartAnimation();

	virtual ~Resources();
private:
	Image * backgroundImage;
	/***** Animacion personaje *****/
	/*Color*/
	SpriteSheet * characterSpriteSheet;
	Animation * characterAnimationLeft;
	Animation * characterAnimationRight;

	SpriteSheet * characterWalk;
	Animation * characterWalkRight;
	Animation * characterWalkLeft;

	SpriteSheet * characterJump;
	Animation * characterStaticLeft;
	Animation * characterStaticRight;
	Animation * characterAirLeft;
	Animation * characterAirRight;

	Animation * topJumpRight;
	Animation * topJumpLeft;
	/*B&W*/
	SpriteSheet * characterSpriteSheetBW;
	Animation * characterAnimationLeftBW;
	Animation * characterAnimationRightBW;

	SpriteSheet * characterWalkBW;
	Animation * characterWalkRightBW;
	Animation * characterWalkLeftBW;

	SpriteSheet * characterJumpBW;
	Animation * characterStaticLeftBW;
	Animation * characterStaticRightBW;
	Animation * characterAirLeftBW;
	Animation * characterAirRightBW;

	Animation * topJumpRightBW;
	Animation * topJumpLeftBW;
	/***** Fin animacion personaje*****/

	SpriteSheet * emoticons;
	Animation * sleepingEmoticon;
	Animation * heartAnimation;
	Animation * exclamationAnimation;

	TTF_Font * nameFonts;

	void loadColoredAnimations();
	void loadBWAnimations();
};

#endif /* RESOURCES_H_ */
