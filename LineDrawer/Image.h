#pragma once

#include "Pixel.h"
#include "Location.h"
#include "Renderer.h"

class Image
{
public:
	virtual ~Image() = 0;
	virtual Pixel getPixel(Location location) = 0;
	virtual void setPixel(Location location, Colour pixel) = 0;
	virtual std::set<Colour, ColourComp> getPalette() = 0;
	virtual void draw(Renderer& renderer) = 0;
};

