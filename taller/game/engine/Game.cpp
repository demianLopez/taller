/*
 * Game.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "Game.h"
#include "Image.h"
#include "Graphics.h"
#include "../../common/Logger.h"
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

	Logger::customLog("Game.cpp", Logger::INFO, "Inicilizando componentes SDL");

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		Logger::customLog("Game.cpp", Logger::ERROR, "SDL No pudo inicializar correctamente");
		success = false;
	} else {
		Logger::customLog("Game.cpp", Logger::INFO, "SDL Initialize: OK");
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);

		if(gWindow == NULL)
		{
			Logger::customLog("Game.cpp", Logger::ERROR, "No se ha podido crear la ventana de SDL"); //SDL_GetError()
			success = false;
		}
		else
		{
			Logger::customLog("Game.cpp", Logger::INFO, "Ventana creada");
			//Get window surface
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
            	Logger::customLog("Game.cpp", Logger::ERROR, "No se pudo inicializar componente SDL_image");
                success = false;
            } else {
            	Logger::customLog("Game.cpp", Logger::INFO, "Inicializado SDL_image");
                if(TTF_Init() == -1) {
                	   Logger::customLog("Game.cpp", Logger::ERROR, "No se pudo inicializar componente SDL_ttf");

                       success = false;
                } else {
                	Logger::customLog("Game.cpp", Logger::INFO, "Inicializado SDL_ttf");
                	this->gFont = TTF_OpenFont( "Resources/font.ttf", 28 );
                	GameElements::gFont = this->gFont;
                }

            	this->gScreenSurface = SDL_GetWindowSurface(gWindow);

            	//Definimos GAME ELEMENTS
            	GameElements::gScreenSurface = this->gScreenSurface;
            	GameElements::gRenderer = this->gRenderer;


            	Logger::customLog("Game.cpp", Logger::INFO, "Componentes SDL Inicializados!");
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
	Logger::customLog("Game.cpp", Logger::INFO, "Comenzando el ciclo de juego");
	if(this->sfps){
		std::stringstream asd;
		asd.str("");
		asd<<"Seteados maximos FPS a: "<<this->maxFPS;

		Logger::customLog("Game.cpp", Logger::INFO, asd.str().c_str());
		asd.clear();
	}

	Graphics *g = new Graphics(this->gFont);

	SDL_Event e;

	//Antes de arrancar el ciclo, llamamos a la funcion init
	Logger::customLog("Game.cpp", Logger::INFO, "Llamado a metodo de inicializacion");
	this->init();
	Logger::customLog("Game.cpp", Logger::INFO, "Inicializacion realizada exitosamente");

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

		this->renderCount++;

		if((SDL_GetTicks() - this->lastFPSUpdateTime) > 1000){
			this->fps = this->renderCount;
			this->renderCount = 0;
			this->lastFPSUpdateTime = SDL_GetTicks();
		}

		if(this->sfps){
			fpsText.clear();
			fpsText.str("");
			fpsText<<this->getFPS()<< " FPS";
			g->drawText(10, 10, fpsText.str().c_str());
		}

		SDL_RenderPresent(gRenderer);

	}

	Logger::customLog("Game.cpp", Logger::INFO, "Finalizando ciclo de juego");
	Logger::customLog("Game.cpp", Logger::INFO, "Llamando a la funcion de cierre");
	this->exit();
	Logger::customLog("Game.cpp", Logger::INFO, "Funcion de cierre finalizada");
	Logger::customLog("Game.cpp", Logger::INFO, "Cerrando componentes de SDL");
	this->gameClose();
	return continues;
}


void Game::gameClose(){

	SDL_DestroyWindow(this->gWindow);
	Logger::customLog("Game.cpp", Logger::INFO, "Ventana destruida");
	SDL_DestroyRenderer(this->gRenderer);
	Logger::customLog("Game.cpp", Logger::INFO, "Render destruido");
	TTF_CloseFont(gFont);
	Logger::customLog("Game.cpp", Logger::INFO, "Fuente cerrada");

	this->gWindow = NULL;
	this->gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	Logger::customLog("Game.cpp", Logger::INFO, "SDL cerrado: OK");
	IMG_Quit();
	Logger::customLog("Game.cpp", Logger::INFO, "SDL Image cerrado: OK");
	TTF_Quit();
	Logger::customLog("Game.cpp", Logger::INFO, "SDL TTF cerrado: OK");
}

Game::~Game() {
	this->fpsText.clear();
}

