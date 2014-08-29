/*
 * Game.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Game.h"
#include "Image.h"
#include "Graphics.h"

Game::Game(const char *title) {
	//Seteo por default
	this->height = 600;
	this->width = 800;
	this->gWindow = NULL;
	this->gScreenSurface = NULL;
	this->gRenderer = NULL;
	this->title = title;
	this->quit = false;
}

void Game::setScreenSize(int height, int width){
	this->height = height;
	this->width = width;
}

bool Game::start(){
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN );
		if(gWindow == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            } else {
            	this->gScreenSurface = SDL_GetWindowSurface(gWindow);

            	//Definimos GAME ELEMENTS
            	GameElements::gScreenSurface = this->gScreenSurface;
            	GameElements::gRenderer = this->gRenderer;

            	//Arrancamos el gameCicle
            	this->gameCicle();
            }
		}
	}

	return success;
}

void Game::endGame(){
	this->quit = true;
}

void Game::gameCicle(){

	Graphics *g = new Graphics();

	SDL_Event e;

	//Antes de arrancar el ciclo, llamamos a la funcion init
	this->init();

	while(!this->quit) {
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				this->endGame();
			} else {
				this->update(e);
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);

		this->render(g);

		SDL_RenderPresent(gRenderer);
		//SDL_UpdateWindowSurface(gWindow);
	}

	this->exit();
	this->gameClose();
}

void Game::gameClose(){
	/*
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;
	*/
	//Destroy window
	SDL_DestroyWindow(this->gWindow);
	SDL_DestroyRenderer(this->gRenderer);
	this->gWindow = NULL;
	this->gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

