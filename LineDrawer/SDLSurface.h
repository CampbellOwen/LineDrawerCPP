#pragma once
#include "Image.h"
#include "stdafx.h"

class SDLSurface :
	public Image
{
public:
	SDLSurface( std::string path, SDL_Surface* screenSurface );
	~SDLSurface();
	Pixel getPixel(Location location);
	void setPixel(Location location, Colour colour);
	std::set<Colour, ColourComp> getPalette();
private:
	SDL_Surface * surface;
	Colour toColour(Uint32 c);
};

