/**
 window.h

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
#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL_stdinc.h>
#include <string>

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;

class Window {

	friend class Sprite;

private:
	SDL_Window* window;
	SDL_Renderer* window_render;

public:
	Window() :
			window(NULL), window_render(NULL) {
	} //TODO: ver
	/**
	 * Crea una ventana con el titulo y las dimensiones especificadas
	 */
	Window(const std::string& title, int widht, int height, int flags);

	virtual ~Window() {
	} //TODO: ver tambien
	/**
	 * Dibuja en la pantalla el contenido almacenado en el render de
	 * la ventana
	 */
	void render();
	/**
	 * Limpia el contenido almacenado del render
	 */
	void clear();
	/**
	 * Dibija sobre el render la textura pasada como parametro
	 */
	void draw_on(SDL_Texture& source_sprite, SDL_Rect& source_rect,
			SDL_Rect& dest_rect);
	/**
	 * Muestra un cuadro de dialogo asociado a la ventana
	 * Flags:
	 * SDL_MESSAGEBOX_ERROR
	 * SDL_MESSAGEBOX_WARNING
	 * SDL_MESSAGEBOX_INFORMATION
	 */
	void show_message_box(Uint32 flags, const std::string& title,
			const std::string& message);
	/**
	 * Libera los recursos de la ventana
	 */
	void free();
};

#endif /* WINDOW_H_ */
