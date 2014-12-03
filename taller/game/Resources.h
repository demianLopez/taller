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

#include "../common/CommandCode.h"
#include "engine/LibIncludes.h"
#include "engine/Music.h"
#include "engine/Sound.h"

class Resources {
public:
	Resources();

	void loadBackground(const char * bPath);
	void loadImage(const char * iPath);
	void loadMusicAndSounds();

	Music * mainMenu;
	Music * levelState;
	Music * gameOver;
	Music * levelPass;

	Sound * golpe;

	Image * getBonusByType(int type);

	void loadAnimations();

	Animation * getShootAnimation();

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

	Animation * getEnemyAnimationByCode(AnimationCode animationCode);
	Animation * getEnemy2AnimationByCode(AnimationCode animationCode);

	Image * getSnowBalLevel(AnimationCode snowBallLevel);

	Animation * getSleepingEmoticon();
	Animation * getExclamationAnimation();

	Image * getBackground();

	TTF_Font * getNameFont();
	TTF_Font * getGuiFont();

	Animation * getHeartAnimation();
	Image * getEnemyProjectile();

	virtual ~Resources();

	Animation* getBossAnimationLeft() const {
		return bossAnimationLeft;
	}

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

	SpriteSheet * bonusSprites;

	Image * bonus1;
	Image * bonus2;
	Image * bonus3;
	Image * bonus4;

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
	/*Enemigos*/

	SpriteSheet * enemy1Sprite;
	Animation * enemyWalkRight;
	Animation * enemyWalkLeft;
	Animation * enemyStaticLeft;
	Animation * enemyStaticRight;
	Animation * enemyAirLeft;
	Animation * enemyAirRight;
	Animation * enemyOnSnowBall;

	SpriteSheet * enemy2Sprite;
	Animation * enemy2WalkRight;
	Animation * enemy2WalkLeft;
	Animation * enemy2StaticLeft;
	Animation * enemy2StaticRight;
	Animation * enemy2AirLeft;
	Animation * enemy2AirRight;
	Animation * enemy2OnSnowBall;

	SpriteSheet * snowBallLevels;
	Image * snowBallLevel1;
	Image * snowBallLevel2;
	Image * snowBallLevel3;
	Image * snowBallLevel4;

	SpriteSheet * shootSprite;
	Animation * shootAnimation;

	SpriteSheet * emoticons;
	Animation * sleepingEmoticon;
	Animation * heartAnimation;
	Animation * exclamationAnimation;

	SpriteSheet * enemigo;
	Animation * bossAnimationRight;
	Animation * bossAnimationLeft;

	Image * enemyProjectile;

	TTF_Font * nameFonts;
	TTF_Font * GUI_Font;

	void loadColoredAnimations();
	void loadBWAnimations();
};

#endif /* RESOURCES_H_ */
