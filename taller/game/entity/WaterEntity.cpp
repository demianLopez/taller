/*
 * WaterEntity.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: maxi
 */

#include <entity/WaterEntity.h>

static const char * WATER_PATH = "Resources/water.png";

WaterEntity::WaterEntity(int index) : GameEntity(index) {
	this->waterImage = NULL;

}

void WaterEntity::initialize(){
	this->waterImage = new Image(WATER_PATH);
}

void WaterEntity::render(Graphics * g, unsigned int dela){
	VectorXY sdlPos = this->gameWorld->box2DToSDL(&position);

	g->drawAtCenter(true);
	g->drawImage(this->waterImage, sdlPos.x, sdlPos.y);
	g->drawAtCenter(false);
}

void WaterEntity::update(unsigned int delta){
	return; // no se puede updetear, es agua.
}

void WaterEntity::addUpdateRequest(UpdateRequest * u, unsigned int currentTime){
	return; //idem update.
}

WaterEntity::~WaterEntity() {
	if(this->waterImage) delete this->waterImage;

}

