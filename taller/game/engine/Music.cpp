/*
 * Music.cpp
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#include "Music.h"

Music::Music(const char * rute) {

	gMusic = Mix_LoadMUS(rute);

	 if( gMusic == NULL ) {
		 printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	 }

}

void Music::stop(){
	Mix_HaltMusic();
}

bool Music::playingMusic(){
	return Mix_PlayingMusic() != 0;
}

void Music::play(int times){


	 Mix_PlayMusic( gMusic, times );

}

Music::~Music() {
	Mix_FreeMusic(gMusic);
}

