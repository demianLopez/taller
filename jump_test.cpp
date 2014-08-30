/**
 jump_test.cpp

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

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "libs/window/window.h"
#include "libs/sprite/sprite.h"

//Constantes del mundo
const float32 timeStep = 1 / 20.0; 	//Tiempo de la simulacion del mundo
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

int main() {

	//Inicializo los componentes de SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Creo una ventana
	Window game_window = Window("Megaman NT Warriors", 1000, 1000, 0);

	//Esto deberia ser una clase en si --------------------------
	Sprite player = Sprite("./res/players/player1.png", game_window);

	b2BodyDef base_body;
	base_body.type = b2_kinematicBody;
	base_body.position.Set(500, 500);
	base_body.angle = 0;

	b2Vec2 gravity(0, -9.8);
	b2World world = b2World(gravity);
	world.SetGravity(gravity);

	b2Body* full_body = world.CreateBody(&base_body);
	full_body->SetLinearVelocity(b2Vec2(100, 0));

	/*Ciclo principal*/
	bool running = true;
	while (running) {

		player.draw(game_window);
		game_window.render();
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 body_position = full_body->GetPosition();
		player.move(body_position.x, body_position.y);

		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {

			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				//Keypress handle
				break;

			}
		}

		SDL_Delay(20);

	}


}
