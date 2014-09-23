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

	Animation * characterStaticLeft;
	Animation * characterStaticRight;
};

#endif /* RESOURCES_H_ */
