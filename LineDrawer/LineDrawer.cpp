// LineDrawer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

int main()
{
	SDLRenderer renderer;
	SDLSurface bunny("bunny.jpg", renderer );
	SDL_Delay(10000);
    return 0;
}

