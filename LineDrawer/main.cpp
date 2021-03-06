// LineDrawer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LineDrawer.h"
#include "Timer.h"
int main()
{
	SDL_Event event;

	SDLRenderer renderer;
	SDLSurface img("hedar_small.jpg", renderer );
	//renderer.Render(bunny);
	SDL_Delay(500);
	LineDrawer drawer(renderer, img);
	drawer.init();

	const int FRAMES_PER_SECOND = 30;
	int frame = 0;
	bool cap = 0;
	Timer fps;
	bool quit = false;

	while (!quit) {
		fps.start();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
				else if (event.key.keysym.sym == SDLK_RETURN ) {
					cap = !cap;;
				}
			}
			else if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		renderer.Render(*(drawer.update()));

		frame++;
		if ( cap && fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}

    return 0;
}

