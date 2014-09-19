/*
 * Game.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Game.h"
#include "Image.h"
#include "Graphics.h"
#include <stdio.h>


Game::Game(const char *title) {
	//Seteo por default
	this->height = 600;
	this->width = 800;
	this->gWindow = NULL;
	this->gScreenSurface = NULL;
	this->gRenderer = NULL;
	this->title = title;
	this->quit = false;
	this->fps = 0;
	this->renderCount = 0;
	this->lastUpdateTime = 0;
	this->lastFPSUpdateTime = 0;
	this->gFont = NULL;
	this->limitedFPS = false;
	this->maxFPS = 0;
	this->lastRenderTime = 0;
	this->sfps = 0;
}

int Game::getScreenHeight(){
	return this->height;
}

int Game::getScreenWidth(){
	return this->width;
}

void Game::showFPS(bool showFPS){
	this->sfps = showFPS;
}
void Game::setMaxFPS(int maxFPS){
	this->limitedFPS = true;
	this->maxFPS = maxFPS;
}

void Game::setScreenSize(int width, int height){
	this->height = height;
	this->width = width;
}

unsigned int Game::getFPS(){
	return this->fps;
}

unsigned int Game::getElapsedTime(){
	return SDL_GetTicks();
}

bool Game::start(){
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
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

                if(TTF_Init() == -1) {
                       printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                       success = false;
                } else {
                	this->gFont = TTF_OpenFont( "Resources/font.ttf", 28 );
                }

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

	Graphics *g = new Graphics(this->gFont);

	SDL_Event e;

	//Antes de arrancar el ciclo, llamamos a la funcion init
	this->init();

	while(!this->quit) {
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				this->endGame();
			} else {
				this->keyEvent(e);
			}
		}

		if(this->limitedFPS){
			int renderTime = 1000 / this->maxFPS;
			int elapsedTime = SDL_GetTicks() - this->lastRenderTime;
			if(elapsedTime < renderTime){
				SDL_Delay(renderTime - elapsedTime);
			}
		}

		g->resetGraphics();

		int delta = SDL_GetTicks() - this->lastUpdateTime;
		this->update(delta);
		this->lastUpdateTime = SDL_GetTicks();

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);


		this->render(g);
		this->lastRenderTime = SDL_GetTicks();

		if(this->sfps){
			fpsText.clear();
			fpsText.str("");
			fpsText<<this->getFPS()<< " FPS";
			g->drawText(10, 10, fpsText.str().c_str());
		}

		this->renderCount++;

		if((SDL_GetTicks() - this->lastFPSUpdateTime) > 1000){
			this->fps = this->renderCount;
			this->renderCount = 0;
			this->lastFPSUpdateTime = SDL_GetTicks();
		}

		SDL_RenderPresent(gRenderer);

	}

	this->exit();
	this->gameClose();
}


void Game::gameClose(){
	SDL_DestroyWindow(this->gWindow);
	SDL_DestroyRenderer(this->gRenderer);
	TTF_CloseFont(gFont);

	this->gWindow = NULL;
	this->gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

Game::~Game() {
	this->fpsText.clear();
}

