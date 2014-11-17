/*
 * Particle.cpp
 *
 *  Created on: 11/9/2014
 *      Author: EscDemi
 */

#include "Particle.h"
#include "ParticleEmiter.h"
#include "Graphics.h"
#include <math.h>

Particle::Particle(ParticleEmiter *emiter, int posX, int posY) {
	this->positionX = posX;
	this->positionY = posY;
	this->emiter = emiter;
	this->timeElpased = 0;
}

void Particle::restart(int posX, int posY) {
	this->positionX = posX;
	this->positionY = posY;
	this->timeElpased = 0;
}

void Particle::update(int delta) {
	this->timeElpased += delta;

	float seconds = (float) delta / 1000;
	float secondsElapsed = (float) this->timeElpased / 1000;

	this->positionX += -300 * seconds;
	this->positionY += (300 + 150 * cos(secondsElapsed * 3.14f)) * seconds;

	if (this->positionX < 0 || this->positionY > 600) {
		this->emiter->restartParticle(this);
	}
}

void Particle::render(Graphics *g) {
	g->drawImage(this->emiter->getParticleImage(), this->positionX,
			this->positionY);
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

