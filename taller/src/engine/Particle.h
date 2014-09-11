/*
 * Particle.h
 *
 *  Created on: 11/9/2014
 *      Author: EscDemi
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

class ParticleEmiter;
class Graphics;

class Particle {
public:
	Particle(ParticleEmiter * emiter, int posX, int posY);
	int getParticleNumber();
	void restart(int posX, int posY);
	void render(Graphics *g);
	void update(int delta);
	virtual ~Particle();
private:
	ParticleEmiter * emiter;
	int positionX;
	int positionY;
	int timeElpased;
};

#endif /* PARTICLE_H_ */
