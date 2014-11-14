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
	this->globalX = 0;
	this->globalY = 0;
	//Se recalcula despues, sabiendo los datos del mundo y la pantalla
	this->maxZoomScale = 1;
	this->hasMessage = false;
	this->messageTime = 0;
	this->serverMessage = NULL;
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

void LevelState::restartCameraPosition(){
	int screenW = Global::game->getScreenWidth();
	int screenH = Global::game->getScreenHeight();
	VectorXY mainEntityPos = Global::gameWorld->getMainEntity()->getPosition();
	VectorXY mainEntitySdlPos = Global::gameWorld->box2DToSDL(&mainEntityPos);

	this->globalX = mainEntitySdlPos.x - screenW/2;
	this->globalY = mainEntitySdlPos.y - screenH/2;
}

void LevelState::render(Graphics *g, Game * game, unsigned int delta){
	levelStateMutex.lock();
	//CALCULOS PREVIOS A RENDER!



	//b2Vec2 playerPos = this->gameWorld->getMainCharacter()->getBody()->GetPosition();


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

	/*
	if(!this->lightAnimation->isFinished()){
		g->drawAnimation(this->lightAnimation, this->lightAnimationX, 0);
	}
	*/
	this->backParticleEmiter->render(g);


	//ALL THE MAP RENDERING!
	//--------------------------------------------------------------------
	g->setRendererObject(this->worldImage);
	g->setColor(0, 0, 0, 0);
	g->clearRenderObject();
	g->setColor(0, 0, 0, 255);


	vector<GameEntity *> entityList = this->gameWorld->getEntityList();
	for(auto * e : entityList){
		e->render(g, delta);
	}



	g->drawAtCenter(true);

	/* TODO: PLAYER MOVIMIENTO CORREGIR!
	b2Vec2 playerSize = this->gameWorld->getMainCharacter()->getSize();
	playerSize =  this->gameWorld->box2DToSDLSize(&playerSize);

	g->drawAnimation(gameWorld->getMainCharacter()->getAnimation(resources), playerPos.x, playerPos.y, playerSize.x, playerSize.y);


	*/

	VectorXY mainEntPos = gameWorld->getMainEntity()->getPosition();
	VectorXY mainEntSdlPos = gameWorld->box2DToSDL(&mainEntPos);



	int dTx = screenW * this->zoomScale;
	int dTy = screenH * this->zoomScale;

	int difTx = (screenW - dTx)/2;
	int difTy = (screenH - dTy)/2;

	int auGlobalX = globalX +difTx;
	int auGlobalY = globalY +difTy;

	float xScreen = mainEntSdlPos.x - auGlobalX;
	float yScreen = mainEntSdlPos.y - auGlobalY;

	if(xScreen < 200){
		globalX -= 5;
	} if(xScreen > dTx - 200){
		globalX += 5;
	} if(yScreen < 200){
		globalY -= 5;
	} if(yScreen > dTy - 100){
		globalY += 5;
	}

	VectorXY sdlWorldSize = this->gameWorld->getSdlWorldSize();

	if((auGlobalX) < 0){
		auGlobalX = 0;
	} if((auGlobalY) < 0){
		auGlobalY = 0;
	} if(auGlobalX > (sdlWorldSize.x - dTx)){
		auGlobalX = sdlWorldSize.x - dTx;
	} if(auGlobalY > (sdlWorldSize.y - dTy)){
		auGlobalY = sdlWorldSize.y - dTy;
	}



	g->setRendererObject(NULL);
	g->drawAtCenter(false);

	g->drawImage(this->worldImage, 0, 0, auGlobalX, auGlobalY, dTx, dTy, screenW, screenH);
	//POST RENDERING!!!
	//-----------------------------------------------------------------------------
	this->frontParticleEmiter->render(g);
	g->setColor(0, 255, 0);
	g->drawFillRect(10, 10, 160, 40);
	g->drawFillRect(190, 10, 420, 40);
	g->drawFillRect(630, 10 , 160, 40);
	g->setColor(0, 0, 0);
	g->drawRect(11, 11, 158, 38);
	g->drawRect(191, 11, 418, 38);
	g->drawRect(631, 11, 158, 38);

	g->setColor(255, 0, 0);
	g->setFont(Global::gameResources->getNameFont());

	if(this->hasMessage){
		g->drawText(400 - messageSize * 5, 15, serverMessage);
		g->drawAnimation(Global::gameResources->getExclamationAnimation(), 400 - messageSize * 5 - 36, 14);
		g->drawAnimation(Global::gameResources->getExclamationAnimation(), 400 + messageSize * 5, 14);

	}

	g->drawText(635, 15, "Puntaje: 0");
	for(int i = 0; i < 5; i++){
		g->drawAnimation(Global::gameResources->getHeartAnimation(), 10 + i* 32, 14);
	}
	levelStateMutex.unlock();
}

void LevelState::keyEvent(SDL_Event e, Game * game) {
	levelStateMutex.lock();
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				this->keyCodeData.push_back(MOVE_LEFT_DOWN);
				break;
			case SDLK_RIGHT:
				this->keyCodeData.push_back(MOVE_RIGHT_DOWN);
				break;
			case SDLK_UP:
				this->keyCodeData.push_back(JUMP);
				break;
			case SDLK_z:
			case SDLK_KP_MINUS:
				this->zoomScale += ZOOM_INCREMENT;
				if(this->zoomScale > this->maxZoomScale){
					this->zoomScale = this->maxZoomScale;
				}
				break;
			case SDLK_x:
			case SDLK_KP_PLUS:
				this->zoomScale -= ZOOM_INCREMENT;
				if(this->zoomScale < this->minZoomScale){
					this->zoomScale = this->minZoomScale;
				}

				break;
		}
		levelStateMutex.unlock();
		return;
	}

	if (e.type == SDL_KEYUP) {
		Message m;
		m.addCommandCode(KEY_EVENT);
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				this->keyCodeData.push_back(MOVE_LEFT_UP);
				break;
			case SDLK_RIGHT:
				this->keyCodeData.push_back(MOVE_RIGHT_UP);
				break;
		}
	}
	levelStateMutex.unlock();
}

void LevelState::sendKeyData(){
	levelStateMutex.lock();
	Message m;

	if(keyCodeData.size() == 0){
		levelStateMutex.unlock();
		return;
	}

	m.addCommandCode(KEY_EVENT);
	m.addChar(keyCodeData.size());

	for(auto keyCode : keyCodeData){
		m.addKeyEventCode(keyCode);
	}

	m.addEndChar();
	Global::client->send_message(&m);

	keyCodeData.clear();
	levelStateMutex.unlock();
}

std::vector<KeyCode> LevelState::getKeyCodeData(){
	return keyCodeData;
}


void LevelState::update(unsigned int delta){
	levelStateMutex.lock();
	this->gameWorld->update(delta);

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


	if(this->hasMessage){
		this->messageTime += delta;
		if(this->messageTime > 10000){
			this->hasMessage = false;
		}
	}

	this->aliveTime += delta;

	if(this->aliveTime > 500){
		Message m;
		m.addCommandCode(IM_ALIVE);
		m.addEndChar();
		Global::client->send_message(&m);
		aliveTime = 0;
	}
	levelStateMutex.unlock();
}

void LevelState::setMessage(char * message){
	levelStateMutex.lock();
	if(serverMessage != NULL){
		delete serverMessage;
		serverMessage = NULL;
	}
	this->serverMessage = message;
	this->messageSize = strlen(message);
	this->hasMessage = true;
	this->messageTime = 0;
	levelStateMutex.unlock();
}

void LevelState::enter(){
	VectorXY wSize = this->gameWorld->getBox2DWorldSize();
	this->worldImage = new Image(wSize.x * 20, wSize.y * 20);
	this->gameWorld->generateGraphics();

	//Recalculamos con datos
	//TODO: Cambiar! por el valor de la pantalla no harcodeado
	float xMax = ((float)wSize.x * 20)/Global::game->getScreenWidth();
	float yMax = ((float)wSize.y * 20)/Global::game->getScreenHeight();

	//---------------------------------------------

	if(xMax > yMax){
		this->maxZoomScale = yMax;
	} else {
		this->maxZoomScale = xMax;
	}
}

LevelState::~LevelState() {
	if(serverMessage != NULL){
		delete serverMessage;
	}
}

