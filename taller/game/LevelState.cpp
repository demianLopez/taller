/*
 * LevelState.cpp
 *
 *  Created on: 17/10/2014
 *      Author: demian
 */

#include "LevelState.h"
#include "VectorXY.h"
#include <iostream>
#include "Global.h"
#include "entity/GameEntity.h"


const float ZOOM_INCREMENT = 0.02;

LevelState::LevelState() {
	this->gameWorld = NULL;
	this->backParticleEmiter = NULL;
	this->frontParticleEmiter = NULL;
	this->worldImage = NULL;
	this->zoomScale = 1;
	this->minZoomScale = 1;
	this->lightAnimationX = 0;
	this->centroX = 0;
	this->centroY = 0;
	//Se recalcula despues, sabiendo los datos del mundo y la pantalla
	this->maxZoomScale = 1;

}


void LevelState::init(Game * game){
	//ADICIONALES!
	//Estos son extras, despues hay que cambiarlos!

	Global::levelState = this;

	this->backgroundImage = new Image("Resources/font1.png");
	this->backParticleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->backParticleEmiter->setMaxParticles(20);

	this->frontParticleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->frontParticleEmiter->setMaxParticles(20);

	this->spriteLightAnimation = new SpriteSheet("Resources/luz.png", 128,512);
	this->lightAnimation = new Animation();
	this->lightAnimation->setOneDraw();
	this->lightAnimation->setFinished(true);

	for(int i = 0; i<8; i++){
		this->lightAnimation->addFrame(this->spriteLightAnimation->getSubImage(i, 0), 25);
	}



	//Recalculamos con datos
	//TODO: Cambiar! por el valor de la pantalla no harcodeado
	//float xMax = ((float)wSize->x * 20)/this->getScreenWidth();
	//float yMax = ((float)wSize->y * 20)/this->getScreenHeight();
	//float xMax = ((float)wSize.x * 20)/800;
	//float yMax = ((float)wSize.y * 20)/600;
	//---------------------------------------------
	/*if(xMax > yMax){
		this->maxZoomScale = yMax;
	} else {
		this->maxZoomScale = xMax;
	}*/

}

void LevelState::setWorld(GameWorld * world){
	this->gameWorld = world;
}

void LevelState::exit(Game * game){

	delete this->lightAnimation;
	delete this->spriteLightAnimation;
	delete this->gameWorld;
	delete this->backParticleEmiter;
	delete this->frontParticleEmiter;
	delete this->worldImage;
	delete this->backgroundImage;
}

void LevelState::render(Graphics *g, Game * game){
	//CALCULOS PREVIOS A RENDER!

	VectorXY box2dWorld = gameWorld->getBox2DWorldSize();
	//b2Vec2 playerPos = this->gameWorld->getMainCharacter()->getBody()->GetPosition();
	VectorXY playerPos(10, 10);

	//TODO SCROLLING MAL ARMADO CORREGIR!
	/*
	b2Vec2 fontPlayerPos(playerPos.x/box2dWorld->x * backImage->getWidth(),
			backImage->getHeight() - playerPos.y/box2dWorld->y * backImage->getHeight());

	playerPos = gameWorld->box2DToSDL(&playerPos);
	*/

	//TODO: Corregir!
	//int screenW = this->getScreenWidth();
	//int screenH = this->getScreenHeight();


	int screenW = game->getScreenWidth();
	int screenH = game->getScreenHeight();
	/*
	//------------------------------------

	int tdX = screenW * this->zoomScale;
	int tdY = screenH * this->zoomScale;
	int tXo = playerPos.x - tdX/2;
	int tYo = playerPos.y - tdY/2;

	if((tXo + tdX) > worldImage->getWidth()){
		tXo = worldImage->getWidth() - tdX;
	}if(tXo < 0){
		tXo = 0;
	}if((tYo + tdY) > worldImage->getHeight()){
		tYo = worldImage->getHeight() - tdY;
	}if(tYo < 0){
		tYo = 0;
	}
	*/

	if(this->backgroundImage != NULL){
		g->drawImage(this->backgroundImage, 0, 0,0,0, screenW, screenH, screenW, screenH);
	}

	if(!this->lightAnimation->isFinished()){
		g->drawAnimation(this->lightAnimation, this->lightAnimationX, 0);
	}
	this->backParticleEmiter->render(g);


	//ALL THE MAP RENDERING!
	//--------------------------------------------------------------------
	g->setRendererObject(this->worldImage);
	g->setColor(0, 0, 0, 0);
	g->clearRenderObject();
	g->setColor(0, 0, 0, 255);


	vector<GameEntity *> entityList = this->gameWorld->getEntityList();
	for(auto * e : entityList){
		e->render(g);
	}



	g->drawAtCenter(true);

	/* TODO: PLAYER MOVIMIENTO CORREGIR!
	b2Vec2 playerSize = this->gameWorld->getMainCharacter()->getSize();
	playerSize =  this->gameWorld->box2DToSDLSize(&playerSize);

	g->drawAnimation(gameWorld->getMainCharacter()->getAnimation(resources), playerPos.x, playerPos.y, playerSize.x, playerSize.y);


	*/
	g->setRendererObject(NULL);

	g->drawAtCenter(false);

	//g->drawImage(this->worldImage, 0, 0, tXo, tYo,tdX, tdY, screenW, screenH);
	g->drawImage(this->worldImage, 0, 0, centroX, centroY,screenW, screenH, screenW, screenH);
	//POST RENDERING!!!
	//-----------------------------------------------------------------------------
	this->frontParticleEmiter->render(g);

}

void LevelState::keyEvent(SDL_Event e, Game * game) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				//this->gameWorld->getMainCharacter()->setMovingLeft(true);
				break;

			case SDLK_RIGHT:
				//this->gameWorld->getMainCharacter()->setMovingRight(true);
				break;

			case SDLK_UP:
				/*if(this->gameWorld->isMainCharacterTouchingGround()){
					this->gameWorld->getMainCharacter()->jump();
				}*/
				break;
			case SDLK_KP_MINUS:
				this->zoomScale += ZOOM_INCREMENT;
				if(this->zoomScale > this->maxZoomScale){
					this->zoomScale = this->maxZoomScale;
				}
				break;
			case SDLK_KP_PLUS:
				this->zoomScale -= ZOOM_INCREMENT;
				if(this->zoomScale < this->minZoomScale){
					this->zoomScale = this->minZoomScale;
				}

				break;
		}
		return;
	}

	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				//this->gameWorld->getMainCharacter()->setMovingLeft(false);
				break;

			case SDLK_RIGHT:
				//this->gameWorld->getMainCharacter()->setMovingRight(false);
				break;


		}
	}

}


void LevelState::update(unsigned int delta){

	this->backParticleEmiter->update(delta);
	this->frontParticleEmiter->update(delta);
	//this->gameWorld->getMainCharacter()->update();

	if(this->lightAnimation->isFinished()){
		int rN = ((float) rand())/RAND_MAX * 5001;
		if(rN >= 4995){
			this->lightAnimation->reset();
			//this->lightAnimationX = ((float) rand())/RAND_MAX * this->getScreenWidth();
		}
	}

}

void LevelState::enter(){
	VectorXY wSize = this->gameWorld->getBox2DWorldSize();
	this->worldImage = new Image(wSize.x * 20, wSize.y * 20);
	this->gameWorld->generateGraphics();
}

LevelState::~LevelState() {

}

