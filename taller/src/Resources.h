/*
 * Resources.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

class Image;

class Resources {
public:
	Resources();

	void loadBackground(const char * bPath);
	void loadImage(const char * iPath);

	Image * getBackground();

	virtual ~Resources();
private:
	Image * backgroundImage;
};

#endif /* RESOURCES_H_ */
