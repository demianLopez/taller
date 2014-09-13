/*
 * ParticleEmiter.h
 *
 *  Created on: 11/9/2014
 *      Author: EscDemi
 */

#ifndef PARTICLEEMITER_H_
#define PARTICLEEMITER_H_

#include <vector>
using namespace std;

class Image;
class Particle;
class Graphics;

class ParticleEmiter {
public:
	ParticleEmiter(Image * particleImage, int maxParticles);

	void render(Graphics *g);
	void update(int delta);

	Image * getParticleImage();

	void restartParticle(Particle * particle);
	void setMaxParticles(int numParticles);

	virtual ~ParticleEmiter();
private:
	int maxEmiter;

	Particle * createParticle();

	vector<Particle*> particleList;

	Image * particleImage;
};

#endif /* PARTICLEEMITER_H_ */
