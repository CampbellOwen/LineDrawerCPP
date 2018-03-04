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
	SDL_FreeSurface(imgSurface);
	imgSurface = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	SDL_Quit();
}

void SDLRenderer::loadImage(std::string path)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error loading image %s, ERROR:%s\n", path.c_str(), IMG_GetError());
	}
	else {
		imgSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
		if (imgSurface == NULL) {
			printf("Unable to optimize image %s:%s\n", path.c_str(), SDL_GetError());
		}

		SDL_RenderSetLogicalSize(renderer, imgSurface->w, imgSurface->h);

		printf("Bits per pixel: %d\n", imgSurface->format->BitsPerPixel);
		printf("Red mask: %x\n", imgSurface->format->Rmask);
		printf("Green mask: %x\n", imgSurface->format->Gmask);
		printf("Blue mask: %x\n", imgSurface->format->Bmask);
		printf("Alpha mask: %x\n", imgSurface->format->Amask);
		SDL_FreeSurface(loadedSurface);
	}
	SDLSurface s("bunny.jpg", screenSurface);
	std::set<Colour, ColourComp> palette = s.getPalette();
}

void SDLRenderer::draw()
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
