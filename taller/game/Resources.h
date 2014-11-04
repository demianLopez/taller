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

	Animation * getAnimationByAnimationCode(AnimationCode animationCode);

	Image * getBackground();

	virtual ~Resources();
private:
	Image * backgroundImage;

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
};

#endif /* RESOURCES_H_ */
