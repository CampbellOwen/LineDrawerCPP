#include "stdafx.h"
#include "SDLRenderer.h"

SDLRenderer::SDLRenderer()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/ );
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

void SDLRenderer::Render(SDLSurface& surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.getSurface());
	SDL_RenderClear( renderer );
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}

void SDLRenderer::setLogicalSize(int w, int h)
{
	SDL_RenderSetLogicalSize(renderer, w, h);
}

