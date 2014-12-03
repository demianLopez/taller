/*
 * Music.h
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#ifndef MUSIC_H_
#define MUSIC_H_
#include "LibIncludes.h"

class Music {
public:
	Music(const char * sound);
	void play(int times);
	static bool playingMusic();
	static void stop();
	virtual ~Music();
private:
	Mix_Music *gMusic;
};

#endif /* MUSIC_H_ */
