#pragma once
#include "Image.h"
#include "stdafx.h"
#include "SDLRenderer.h"

class SDLSurface :
	public Image
{
public:
	SDLSurface( std::string path, SDLRenderer& renderer );
	~SDLSurface();
	Pixel getPixel(Location location);
	void setPixel(Location location, Colour colour);
	std::set<Colour, ColourComp> getPalette();
	void draw(Renderer& renderer);
private:
	SDL_Surface * surface;
	Colour toColour(Uint32 c);
};

