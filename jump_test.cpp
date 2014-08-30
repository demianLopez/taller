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

int main() {

	SDL_Init(SDL_INIT_VIDEO);

	Window w = Window("Megaman NT Warriors", 1000, 1000, 0);

	Sprite s = Sprite("./res/players/player1.png", w);
	SDL_Rect a = SDL_Rect();

	b2BodyDef b;
	b.type = b2_kinematicBody;
	b.position.Set(500, 500);
	b.angle = 0;

	b.linearVelocity = b2Vec2(1, 0);

	b2Vec2 gravity(0, -9.8);
	bool doSleep = true;
	b2World world = b2World(gravity);

	world.SetGravity(gravity);

	bool running = true;

	float32 timeStep = 1 / 20.0; //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	while (running) {
		s.draw(w);
		w.render();

		world.Step(timeStep, velocityIterations, positionIterations);

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {

			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				break;

			}
		}

		SDL_Delay(20);

	}
}
