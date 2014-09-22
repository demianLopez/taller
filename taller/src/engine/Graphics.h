/*
 * Graphics.h
 *
 *  Created on: 23/8/2014
 *      Author: EscDemi
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "LibIncludes.h"
class Image;
class Animation;

class Graphics {

public:
	Graphics(TTF_Font * font);
	virtual ~Graphics();
	//Renderiza en pantalla la imagen "image"
	void drawImage(Image *image);
	//Renderiza en la pantalla una imagen comenzada a dibujar desde x, y
	void drawImage(Image *image, int x, int y);
	//Renderiza en la pantalla una imagen comenzada a dibujar desde x, y y de longitud dx dy
	void drawImage(Image *image, int xo, int yo, int dx, int dy);

	void drawImage(Image *image, int xo, int yo, int dx, int dy, float rotation);

	void drawImage(Image *image, int xo, int yo, float rotation);

	void drawAnimation(Animation * animation, int xo, int yo);
	void drawAnimation(Animation * animation, int xo, int yo, float rotation);

	//Dibuja un rectamgulo lleno (pintado interiormente)
	void drawFillRect(int xo, int yo, int dx, int dy);

	//Dibuja un rectangulo vacio (solo sus bordes)
	void drawRect(int xo, int yo, int dx, int dy);

	//Dibuja una linea
	void drawLine(int xo, int yo, int xf, int yf);

	//Dibuja un punto
	void drawPoint(int x, int y);

	void drawText(int x, int y, const char* text);

	void drawAtCenter(bool dAtCenter);

	void resetGraphics();

	void drawFillCircle(int x, int y, int rad, int r, int g, int b);
	void drawFillPolygon(short int* vx, short int* vy, int n, int r, int g, int b);

	//Setea el color
	void setColor(unsigned char red, unsigned char green, unsigned char blue);
	void setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
private:
	TTF_Font *currentFont;
	bool dAtCenter;
};

#endif /* GRAPHICS_H_ */
