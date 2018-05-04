#pragma once

#include "stdafx.h"
#include "Image.h"
#include "SDLRenderer.h"
#include <unordered_map>

class SDLRenderer;

class SDLSurface :
	public Image
{
public:
	SDLSurface( std::string path, SDLRenderer& renderer );
	SDLSurface(SDLSurface& other);
	~SDLSurface();
	Pixel getPixel(Location location);
	void setPixel(Location location, Colour colour);
	std::unordered_map<Colour, double, ColourHasher> getPalette();
	SDL_Surface* getSurface();
	int getWidth();
	int getHeight();
private:
	SDL_Surface * surface;
	Colour toColour(Uint32 c);
};

