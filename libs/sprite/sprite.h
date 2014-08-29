/**
 sprite.h

 Copyright 2014 Gaston Martinez Gaston.martinez.90@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses
 */
#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL2/SDL.h>

#include <string>
#include <exception>

#include "../window/window.h"

class Sprite_Construction_Error: public std::exception {
	virtual const char* what() const throw () {
		std::string mensaje = "Ocurrio un error al crear el sprite: ";
		mensaje += SDL_GetError();
		return mensaje.c_str();
	}
};

class Sprite {

protected:

	SDL_Texture* _texture;
	int x_pos;
	int y_pos;

	int image_width;
	int image_height;

	int scaled_width;
	int scaled_height;

public:
	/**
	 * Dummy
	 *
	Sprite() {
	}*/
	virtual ~Sprite() {
	}

	/**
	 * TODO:
	 */
	Sprite(const std::string& file_path, Window& window);

	/**
	 * TODO:
	 */
	Sprite(SDL_Surface& surface, Window& window);

	/**
	 * TODO:
	 */
	Sprite(SDL_Surface& surface, Window& window, int image_width,
			int image_height);
	/**
	 * Setea las posiciones x e y donde debe ser dibujado
	 * el sprite
	 */
	void move(int x_pos, int y_pos);
	/**
	 * Dibuja el sprite en la ventana correspondiente
	 */
	virtual void draw(Window& destination_window);
	/**
	 * Dibuja el sprite en la ventana correspondiente
	 * en la posicion indicada por el rectangulo
	 */
	virtual void draw(Window& destination_window, SDL_Rect& destination_rect);

	/**
	 * Cambia el tamaño final del sprite al ser dibujado en todas
	 * sus dimensiones segun la escala pasada
	 */
	void scale(double scale);
	/**
	 * Cambia el tamaño final del sprite al ser dibujado en
	 * su ancho segun la escala pasada
	 */
	void scale_width(double scale);
	/**
	 * Cambia el tamaño final del sprite al ser dibujado en
	 * su alto segun la escala pasada
	 */
	void scale_height(double scale);
	/**
	 * Cambia el tamaño final del sprite al ser dibujado en
	 * su ancho segun la escala pasada, manteniendo el aspect ratio
	 */
	void scale_with_widht(int scaled_width);
	/**
	 * Cambia el tamaño final del sprite al ser dibujado en
	 * su alto segun la escala pasada, manteniendo el aspect ratio
	 */
	void scale_with_height(int scaled_height);
	/**
	 * Define el tamaño final del sprite al ser dibujado en
	 * su ancho segun el valor pasado
	 */
	void set_scaled_width(int scaled_width);
	/**
	 * Define el tamaño final del sprite al ser dibujado en
	 * su alto segun el valor pasado
	 */
	void set_scaled_height(int scaled_height);

	/**
	 * Setea el nivel de transparencia desde 0 (completamente transparente)
	 * a 255 (completamente opaco)
	 */
	void set_transparency_level(Uint8 level);

	int get_scaled_height() const {
		return scaled_height;
	}

	int get_scaled_width() const {
		return scaled_width;
	}
	/**
	 * Libera la textura asociada al sprite
	 */
	virtual void free();

};

#endif /* SPRITE_H_ */
