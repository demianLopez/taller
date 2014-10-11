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

	void reset();
	void setOneDraw();
	bool isFinished();
	void setFinished(bool finished);
	virtual ~Animation();
private:
	vector<AnimationFrame*> frameList;
	bool drawed;
	unsigned int lastTimeDrawed;
	unsigned int lastDrawedFrame;

	bool drawOneTime;
	bool cicleFinish;
};

#endif /* ANIMATION_H_ */
