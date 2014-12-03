/*
 * Sound.h
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "LibIncludes.h"

class Sound {
public:
	Sound(const char * ruta);
	void play();
	virtual ~Sound();
private:
	Mix_Chunk *gSound;
};

#endif /* SOUND_H_ */
