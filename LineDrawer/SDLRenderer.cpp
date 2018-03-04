#include "stdafx.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"


SDLRenderer::SDLRenderer()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN/* | SDL_WINDOW_FULLSCREEN_DESKTOP*/ );
	renderer = SDL_CreateRenderer(window, -1, 0);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
	if (!( IMG_Init(imgFlags) & imgFlags ) ) {
		printf("SDL_image not initialized: %s\n", IMG_GetError() );
	}

	screenSurface = SDL_GetWindowSurface(window);
}

SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	SDL_Quit();
}

SDL_Surface * SDLRenderer::getScreenSurface()
{
	return screenSurface;
}

SDL_Renderer * SDLRenderer::getRenderer()
{
	return renderer;
}
