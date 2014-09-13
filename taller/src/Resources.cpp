/*
 * Resources.cpp
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#include "Resources.h"
#include "engine/Image.h"

Resources::Resources() {
	this->backgroundImage = NULL;
}

void Resources::loadBackground(const char *bPath){
	this->backgroundImage = new Image(bPath);
}

Image * Resources::getBackground(){
	return this->backgroundImage;
}

Resources::~Resources() {
	if(this->backgroundImage != NULL){
		delete backgroundImage;
	}
}

