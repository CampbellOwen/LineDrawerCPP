// LineDrawer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LineDrawer.h"

int main()
{
	SDLRenderer renderer;
	SDLSurface bunny("bunny.jpg", renderer );
	renderer.Render(bunny);
	SDL_Delay(1000);
	LineDrawer drawer(renderer, bunny);
	drawer.init();
	for (int i = 0; i < 200; i++) {
		renderer.Render(*drawer.update());
		SDL_Delay(25);
	}
    return 0;
}

