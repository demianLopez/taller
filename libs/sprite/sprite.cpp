/**
 sprite.cpp

 Copyright 2013 Gaston Martinez Gaston.martinez.90@gmail.com

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
#include "sprite.h"
#include <SDL2/SDL_image.h>
#include <math.h>

#include <iostream>

using std::string;

Sprite::Sprite(const std::string& file_path, Window& window) {
	_texture = NULL;
	SDL_Surface* temporal = NULL;

	if ((temporal = IMG_Load(file_path.c_str())) == NULL) {
		throw Sprite_Construction_Error();
	}

	image_width = temporal->w;
	image_height = temporal->h;

	_texture = SDL_CreateTextureFromSurface(window.window_render, temporal);
	SDL_FreeSurface(temporal);

	if (_texture == NULL) {
		throw Sprite_Construction_Error();
	}

	this->x_pos = 0;
	this->y_pos = 0;

	scaled_width = image_width;
	scaled_height = image_height;
}

Sprite::Sprite(SDL_Surface& surface, Window& window){
	_texture = SDL_CreateTextureFromSurface(window.window_render, &surface);

	if (_texture == NULL)
		throw Sprite_Construction_Error();

	this->x_pos = 0;
	this->y_pos = 0;

	image_width = surface.w;
	image_height = surface.h;

	scaled_width = image_width;
	scaled_height = image_height;
}

Sprite::Sprite(SDL_Surface& surface, Window& window, int image_width,
		int image_height) {
	_texture = SDL_CreateTextureFromSurface(window.window_render, &surface);

	if (_texture == NULL)
		throw Sprite_Construction_Error();

	this->x_pos = 0;
	this->y_pos = 0;

	this->image_width = image_width;
	this->image_height = image_height;

	scaled_width = image_width;
	scaled_height = image_height;
}

void Sprite::draw(Window& destination_window) {

	SDL_Rect source_rect;
	SDL_Rect destination_rect;

	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = image_width;
	source_rect.h = image_height;

	destination_rect.x = x_pos;
	destination_rect.y = y_pos;
	destination_rect.w = scaled_width;
	destination_rect.h = scaled_height;

	destination_window.draw_on(*_texture, source_rect, destination_rect);

}

void Sprite::draw(Window& destination_window, SDL_Rect& destination_rect) {

	SDL_Rect source_rect;

	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = image_width;
	source_rect.h = image_height;

	destination_window.draw_on(*_texture, source_rect, destination_rect);

}

void Sprite::move(int x_pos, int y_pos) {
	this->x_pos = x_pos;
	this->y_pos = y_pos;
}

void Sprite::scale(double scale) {
	scaled_width = ceil(scaled_width * scale);
	scaled_height = ceil(scaled_height * scale);
}

void Sprite::scale_width(double scale) {
	scaled_width = ceil(scaled_width * scale);
}

void Sprite::scale_height(double scale) {
	scaled_height = ceil(scaled_height * scale);
}

void Sprite::scale_with_widht(int scaled_width) {
	double scale = (this->scaled_height+0.0)/this->scaled_width;
	this->scaled_width = scaled_width;
	this->scaled_height = ceil(scaled_width * scale);
}

void Sprite::scale_with_height(int scaled_height) {
	double scale = (this->scaled_width+0.0)/this->scaled_height;
	this->scaled_height = scaled_height;
	this->scaled_width = ceil(scaled_height * scale);
}

void Sprite::set_scaled_width(int scaled_width) {
	this->scaled_width = scaled_width;
}

void Sprite::set_scaled_height(int scaled_height) {
	this->scaled_height = scaled_height;
}

void Sprite::free() {
    SDL_DestroyTexture(_texture);
}

void Sprite::set_transparency_level(Uint8 level) {
	SDL_SetTextureAlphaMod(_texture,level);
}
