#pragma once
#include "Image.h"
#include "stdafx.h"
#include <vector>

class SDLTexture :
	public Image
{
public:
	SDLTexture( int width, int height, SDLRenderer& renderer );
	~SDLTexture();
	Pixel getPixel(Location location);
	void setPixel(Location location, Colour colour);
	void setPixels(std::vector<Pixel> pixels);

private:
	SDL_Texture * texture;
	Colour toColour(Uint32 c);
};

