#include <SDL2/SDL.h>
#include "libs/window/window.h"
#include "libs/sprite/sprite.h"

int main() {

	SDL_Init(SDL_INIT_VIDEO);

	Window w = Window("Megaman NT Warriors", 1000, 1000, 0);

	Sprite s = Sprite("./n.png", w);
	SDL_Rect a = SDL_Rect();

	bool running = true;

	while (running) {
		s.draw(w);
		w.render();
		SDL_Delay(20);
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0) {

			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					s.move(10,10);
				}
				break;

			}
		}

	}
}
