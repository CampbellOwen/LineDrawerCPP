// LineDrawer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDLRenderer.h"

int main()
{
	SDLRenderer renderer;
	renderer.loadImage("bunny.jpg");
	renderer.draw();
	SDL_Delay(10000);
    return 0;
}

