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

class Graphics {

public:
	Graphics();
	virtual ~Graphics();
	//Renderiza en pantalla la imagen "image"
	void drawImage(Image *image);
	//Renderiza en la pantalla una imagen comenzada a dibujar desde x, y
	void drawImage(Image *image, int x, int y);
	//Renderiza en la pantalla una imagen comenzada a dibujar desde x, y y de longitud dx dy
	void drawImage(Image *image, int xo, int yo, int dx, int dy);

	//Dibuja un rectamgulo lleno (pintado interiormente)
	void drawFillRect(int xo, int yo, int dx, int dy);

	//Dibuja un rectangulo vacio (solo sus bordes)
	void drawRect(int xo, int yo, int dx, int dy);

	//Dibuja una linea
	void drawLine(int xo, int yo, int xf, int yf);

	//Dibuja un punto
	void drawPoint(int x, int y);

	//Setea el color
	void setColor(unsigned char red, unsigned char green, unsigned char blue);
	void setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
private:

};

#endif /* GRAPHICS_H_ */
