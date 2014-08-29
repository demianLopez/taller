/**
 window.cpp

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

#include "window.h"

#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

using std::string;

Window::Window(const string& title, int widht, int height, int flags) {
	SDL_CreateWindowAndRenderer(widht, height, flags, &window, &window_render);
	//TODO: Excepciones durante la creacion
	SDL_SetRenderDrawColor(window_render, 0, 0, 0, 12);

	SDL_SetWindowTitle(window, title.c_str());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	//Setea el render a un tamaño fijo para uqe funcione durante
	//la redimension
	SDL_RenderSetLogicalSize(window_render, widht, height);
}

void Window::clear() {
	SDL_RenderClear(window_render);
}

void Window::render() {
	SDL_RenderPresent(window_render);
}

void Window::draw_on(SDL_Texture& source_sprite, SDL_Rect& source_rect,
		SDL_Rect& dest_rect) {
	SDL_RenderCopy(window_render, &source_sprite, &source_rect, &dest_rect);
}

void Window::free() {
	SDL_DestroyRenderer(window_render);
	SDL_DestroyWindow(window);
}

void Window::show_message_box(Uint32 flags, const string& title,
		const string& message) {
	SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), window);
}
