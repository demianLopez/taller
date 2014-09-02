/*
 * Animation.h
 *
 *  Created on: 30/8/2014
 *      Author: EscDemi
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

using namespace std;

#include "LibIncludes.h"
#include <vector>

class AnimationFrame;
class Image;

class Animation {
public:
	Animation();

	void addFrame(Image * frameImage, int frameTime);
	int getFrameCount();
	AnimationFrame* getFrame(int index);
	AnimationFrame* getCurrentFrame();

	virtual ~Animation();
private:
	vector<AnimationFrame*> frameList;
	bool drawed;
	unsigned int lastTimeDrawed;
	unsigned int lastDrawedFrame;
};

#endif /* ANIMATION_H_ */
