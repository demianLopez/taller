/*
 * Game.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Game.h"
#include "Image.h"
#include "Graphics.h"
#include <Logger.h>
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
	return this->gameCicle();
}

bool Game::instantiate(){
	bool success = true;

	Logger::customLog("Game.cpp", Logger::INFO, "Initializing SDL Components");

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		Logger::customLog("Game.cpp", Logger::ERROR, "SDL could not initialize! SDL_Error: ");
		success = false;
	} else {
		Logger::customLog("Game.cpp", Logger::INFO, "SDL Initialize: OK");
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);

		if(gWindow == NULL)
		{
			Logger::customLog("Game.cpp", Logger::ERROR, "Window could not be created! SDL_Error: "); //SDL_GetError()
			success = false;
		}
		else
		{
			Logger::customLog("Game.cpp", Logger::INFO, "Window created: OK");
			//Get window surface
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
            	Logger::customLog("Game.cpp", Logger::ERROR, "SDL_image could not initialize! SDL_Image_Error: ");
                success = false;
            } else {
            	Logger::customLog("Game.cpp", Logger::INFO, "SDL Image Initialize: OK");
                if(TTF_Init() == -1) {
                	   Logger::customLog("Game.cpp", Logger::ERROR, "SDL_ttf could not initialize! TTF_Error: ");

                       success = false;
                } else {
                	Logger::customLog("Game.cpp", Logger::INFO, "SDL TTF Initialize: OK");
                	this->gFont = TTF_OpenFont( "Resources/font.ttf", 28 );
                	GameElements::gFont = this->gFont;
                }

            	this->gScreenSurface = SDL_GetWindowSurface(gWindow);

            	//Definimos GAME ELEMENTS
            	GameElements::gScreenSurface = this->gScreenSurface;
            	GameElements::gRenderer = this->gRenderer;


            	Logger::customLog("Game.cpp", Logger::INFO, "SDL All components initialized!");
            	//Arrancamos el gameCicle


            }
		}
	}

	return success;
}

void Game::endGame(){
	this->quit = true;
}

bool Game::gameCicle(){
	bool continues = false;
	Logger::customLog("Game.cpp", Logger::INFO, "Starting Game Cicle");
	if(this->sfps){
		std::stringstream asd;
		asd.str("");
		asd<<"Max FPS set at: "<<this->maxFPS;

		Logger::customLog("Game.cpp", Logger::INFO, asd.str().c_str());
		asd.clear();
	}

	Graphics *g = new Graphics(this->gFont);

	SDL_Event e;

	//Antes de arrancar el ciclo, llamamos a la funcion init
	Logger::customLog("Game.cpp", Logger::INFO, "Calling Init function");
	this->init();
	Logger::customLog("Game.cpp", Logger::INFO, "Init function called succesfull");

	while(!this->quit) {
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				this->endGame();
			} else {
				if (e.key.keysym.sym == SDLK_r){
					continues = true;
					this->endGame();
				}else{
					this->keyEvent(e);
				}
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

	Logger::customLog("Game.cpp", Logger::INFO, "Ending game cicle");
	Logger::customLog("Game.cpp", Logger::INFO, "Calling exit function");
	this->exit();
	Logger::customLog("Game.cpp", Logger::INFO, "exit function called succesfull");
	Logger::customLog("Game.cpp", Logger::INFO, "Closing SDL Components");
	this->gameClose();
	return continues;
}


void Game::gameClose(){

	SDL_DestroyWindow(this->gWindow);
	Logger::customLog("Game.cpp", Logger::INFO, "Window destroyed!");
	SDL_DestroyRenderer(this->gRenderer);
	Logger::customLog("Game.cpp", Logger::INFO, "Render destroyed!");
	TTF_CloseFont(gFont);
	Logger::customLog("Game.cpp", Logger::INFO, "Font closed!");

	this->gWindow = NULL;
	this->gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	Logger::customLog("Game.cpp", Logger::INFO, "SDL close: OK");
	IMG_Quit();
	Logger::customLog("Game.cpp", Logger::INFO, "SDL Image close: OK");
	TTF_Quit();
	Logger::customLog("Game.cpp", Logger::INFO, "SDL TTF close: OK");
}

Game::~Game() {
	this->fpsText.clear();
}

