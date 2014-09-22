/*
 * ParticleEmiter.cpp
 *
 *  Created on: 11/9/2014
 *      Author: EscDemi
 */

#include <engine/ParticleEmiter.h>
#include <cstdlib>
#include "Image.h"
#include "Particle.h"
#include "Graphics.h"

ParticleEmiter::ParticleEmiter(Image * particleImage, int maxParticles) {
	this->particleImage = particleImage;
	this->maxEmiter = maxParticles;
}

void ParticleEmiter::setMaxParticles(int numParticles){
	this->maxEmiter = numParticles;
}

Image * ParticleEmiter::getParticleImage(){
	return this->particleImage;
}

void ParticleEmiter::restartParticle(Particle * particle){
	int tx = (((float) rand())/RAND_MAX) * 800;
	int ty = (((float) rand())/RAND_MAX) * 600 *((float)(tx))/800;
	particle->restart(tx, ty);
}

Particle * ParticleEmiter::createParticle(){
	int tx = (((float) rand())/RAND_MAX) * 800;
	int ty = (((float) rand())/RAND_MAX) * 600 *((float)(tx))/800;
	return new Particle(this, tx, ty);
}

void ParticleEmiter::update(int delta){
	for(auto *particle : this->particleList){
		particle->update(delta);
	}

	if(this->particleList.size() < maxEmiter){
		this->particleList.push_back(this->createParticle());
	}
}

void ParticleEmiter::render(Graphics * g){
	for(auto *particle : this->particleList){
		particle->render(g);
	}
}

ParticleEmiter::~ParticleEmiter() {
	for(auto *particle : this->particleList){
		delete particle;
	}

	this->particleList.clear();
}

