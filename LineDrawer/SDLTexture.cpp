#include "stdafx.h"
#include "SDLTexture.h"
#include "SDLSurface.h"


SDLTexture::SDLTexture( int width, int height, SDLRenderer& renderer )
{
	texture = SDL_CreateTexture(renderer.getRenderer(), SDL_BYTESPERPIXEL(4), SDL_TEXTUREACCESS_STREAMING, width, height);
	
}


SDLTexture::~SDLTexture()
{
	SDL_DestroyTexture(texture);
}

Pixel SDLTexture::getPixel(Location location)
{
	return Pixel{ 0, 0 };
}

void SDLTexture::setPixel(Location location, Colour colour)
{

}

void SDLTexture::setPixels(std::vector<Pixel> pixels)
{

}



std::set<Colour, ColourComp> SDLTexture::getPalette()
{
	return std::set<Colour, ColourComp>();
}

Colour SDLTexture::toColour(Uint32 c) 
{
	return Colour{ 0,0,0 };
}
