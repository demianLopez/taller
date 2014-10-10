/*
 * SnowBross.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "SnowBross.h"
#include "engine/Game.h"
#include "engine/Graphics.h"
#include "engine/LibIncludes.h"
#include "engine/ParticleEmiter.h"
#include "engine/Image.h" //Provisional
#include "Personaje.h"

#include "World.h"
#include "Resources.h"

const float ZOOM_INCREMENT = 0.02;
SnowBross::SnowBross(const char *pTitle) : Game(pTitle) {
	this->gameWorld = NULL;
	this->backParticleEmiter = NULL;
	this->frontParticleEmiter = NULL;
	this->worldImage = NULL;
	this->zoomScale = 1;
	this->minZoomScale = 1;

	//Se recalcula despues, sabiendo los datos del mundo y la pantalla
	this->maxZoomScale = 1;
}

void SnowBross::init(){
	//ADICIONALES!
	//Estos son extras, despues hay que cambiarlos!
	this->backParticleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->backParticleEmiter->setMaxParticles(20);

	this->frontParticleEmiter = new ParticleEmiter(new Image("Resources/p.png"), 10);
	this->frontParticleEmiter->setMaxParticles(20);

	b2Vec2 * wSize = this->gameWorld->getBox2DWorldSize();
	this->worldImage = new Image(wSize->x * 20, wSize->y * 20);

	//Recalculamos con datos
	float xMax = ((float)wSize->x * 20)/this->getScreenWidth();
	float yMax = ((float)wSize->y * 20)/this->getScreenHeight();

	Resources * resources = this->gameWorld->getResources();
	Image * backImage = resources->getBackground();

	if(xMax > yMax){
		this->maxZoomScale = yMax;
		this->zoomFontConv =  (float)(backImage->getHeight()) / (wSize->y * 20);
	} else {
		this->maxZoomScale = xMax;
		this->zoomFontConv =  (float)(backImage->getWidth())  / (wSize->x * 20);
	}
}

void SnowBross::setWorld(World * world){
	this->gameWorld = world;
}

void SnowBross::exit(){
	delete this->gameWorld;
	delete this->backParticleEmiter;
	delete this->frontParticleEmiter;
	delete this->worldImage;
}

void SnowBross::render(Graphics *g){
	//CALCULOS PREVIOS A RENDER!
	Resources * resources = this->gameWorld->getResources();
	Image * backImage = resources->getBackground();

	b2Vec2 * box2dWorld = gameWorld->getBox2DWorldSize();
	b2Vec2 playerPos = this->gameWorld->getMainCharacter()->getBody()->GetPosition();

	b2Vec2 fontPlayerPos(playerPos.x/box2dWorld->x * backImage->getWidth(),
			backImage->getHeight() - playerPos.y/box2dWorld->y * backImage->getHeight());

	playerPos = gameWorld->box2DToSDL(&playerPos);

	int screenW = this->getScreenWidth();
	int screenH = this->getScreenHeight();
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

	float pX = (float)(backImage->getWidth() - screenW)/(float)(worldImage->getWidth() - screenW);
	float pY = (float)(backImage->getHeight() - screenH)/(float)(worldImage->getHeight() - screenH);

	if(backImage != NULL){
		g->drawImage(backImage, 0, 0,pX * tXo,pY * tYo, tdX * this->zoomFontConv, tdY * this->zoomFontConv, screenW, screenH);
	}

	this->backParticleEmiter->render(g);


	//ALL THE MAP RENDERING!
	//--------------------------------------------------------------------
	g->setRendererObject(this->worldImage);
	g->setColor(0, 0, 0, 0);
	g->clearRenderObject();
	g->setColor(0, 0, 0, 255);

	vector<Polygon *> polList = this->gameWorld->getPolygonList();
	for(auto *polygon : polList){
		polygon->render(g);
	}


	g->drawAtCenter(true);

	b2Vec2 playerSize = this->gameWorld->getMainCharacter()->getSize();
	playerSize =  this->gameWorld->box2DToSDLSize(&playerSize);

	g->drawAnimation(gameWorld->getMainCharacter()->getAnimation(resources), playerPos.x, playerPos.y, playerSize.x, playerSize.y);


	g->setRendererObject(NULL);

	g->drawAtCenter(false);

	g->drawImage(this->worldImage, 0, 0, tXo, tYo,tdX, tdY, screenW, screenH);

	//POST RENDERING!!!
	//-----------------------------------------------------------------------------
	this->frontParticleEmiter->render(g);

}

void SnowBross::keyEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				this->gameWorld->getMainCharacter()->setMovingLeft(true);
				break;

			case SDLK_RIGHT:
				this->gameWorld->getMainCharacter()->setMovingRight(true);
				break;

			case SDLK_UP:
				if(this->gameWorld->isMainCharacterTouchingGround()){
					this->gameWorld->getMainCharacter()->jump();
				}
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
				this->gameWorld->getMainCharacter()->setMovingLeft(false);
				break;

			case SDLK_RIGHT:
				this->gameWorld->getMainCharacter()->setMovingRight(false);
				break;


		}
	}

}


void SnowBross::update(unsigned int delta){

	this->backParticleEmiter->update(delta);
	this->frontParticleEmiter->update(delta);
	this->gameWorld->worldStep(delta);
	this->gameWorld->getMainCharacter()->update();

}

SnowBross::~SnowBross() {

}

