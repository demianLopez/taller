/*
 * Game.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Game.h"
#include "SDL.h"

Game::Game(const char *title) {
	//Seteo por default
	this->height = 600;
	this->width = 800;
	this->gWindow = NULL;
	this->gScreenSurface = NULL;
	this->title = title;
}

void Game::setScreenSize(int height, int width){
	this->height = height;
	this->width = width;
}

void Game::start(){
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
		if(gWindow == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			this->gameCicle();
		}
	}

}

void Game::gameCicle(){
	bool quit = false;
	SDL_Event e;

	while(!quit) {
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				quit = true;
			} else {
				this->update(e);
			}
		}

		this->render();

		SDL_UpdateWindowSurface(gWindow);
	}

	this->gameClose();
}

void Game::gameClose(){
	/*
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;
	*/
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

