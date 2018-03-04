#include "stdafx.h"
#include "SDLSurface.h"


SDLSurface::SDLSurface( std::string path, SDL_Surface* screenSurface )
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error loading image %s, ERROR:%s\n", path.c_str(), IMG_GetError());
	}
	else {
		surface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
		if (surface == NULL) {
			printf("Unable to optimize image %s:%s\n", path.c_str(), SDL_GetError());
		}

		printf("Bits per pixel: %d\n", surface->format->BitsPerPixel);
		printf("Red mask: %x\n", surface->format->Rmask);
		printf("Green mask: %x\n", surface->format->Gmask);
		printf("Blue mask: %x\n", surface->format->Bmask);
		printf("Alpha mask: %x\n", surface->format->Amask);
		SDL_FreeSurface(loadedSurface);
	}
}

SDLSurface::~SDLSurface()
{
	SDL_FreeSurface(surface);
	surface = NULL;
}

Pixel SDLSurface::getPixel(Location location) {
	Uint32* pixels = (Uint32*)surface->pixels;

	Uint32 pixel = pixels[(location.y * surface->w) + location.x];

	return Pixel{ location, toColour( pixel) };
}

void SDLSurface::setPixel(Location location, Colour colour)
{
	Uint32 c = SDL_MapRGB(surface->format, colour.r, colour.g, colour.b);
	Uint32* pixels = (Uint32*)surface->pixels;
	pixels[(location.y * surface->w) + location.x] = c;
}

std::set<Colour, ColourComp> SDLSurface::getPalette()
{
	std::set<Colour, ColourComp> palette;
	for (int i = 0; i < surface->h * surface->w; i++)
	{
		palette.insert(this->getPixel(Location{ i % surface->w, i / surface->w }).colour);
	}

	return palette;
}

Colour SDLSurface::toColour(Uint32 c)
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	SDL_GetRGB(c, surface->format, &r, &g, &b);

	return Colour{ r, g, b };
}
