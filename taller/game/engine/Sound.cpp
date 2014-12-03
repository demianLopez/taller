/*
 * Sound.cpp
 *
 *  Created on: 03/12/2014
 *      Author: demian
 */

#include <engine/Sound.h>

Sound::Sound(const char * ruta) {
	 gSound = Mix_LoadWAV( ruta);
	 if( gSound == NULL ) {
		 printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	 }
}

void Sound::play(){
	Mix_PlayChannel( -1, gSound, 0 );
}

Sound::~Sound() {
	Mix_FreeChunk( gSound );
}

