#pragma once

#include "stdafx.h"
#include "SDLSurface.h"
#include "SDLRenderer.h"
#include <vector>
#include "Pixel.h"
#include "Location.h"

class LineDrawer
{
public:
	LineDrawer(SDLRenderer& renderer, SDLSurface& referenceImg);
	~LineDrawer();
	void init();
	SDLSurface* update();
	std::unordered_map<Colour, double, ColourHasher> palette;
	float meanSquaredError(Colour c1, Colour c2);
	bool shouldDrawLine(std::vector< Pixel > line);
	
private:
	std::vector<Pixel> getLinePoints(Colour colour, Location p1, Location p2);
	int getOctant(Location p1, Location p2);
	Location toOctantZero(int octant, Location point);
	Location octantZeroTo(int octant, Location point);
	Colour getRandomColour( bool weighted );
	SDLRenderer& renderer;
	SDLSurface& referenceImg;
	SDLSurface* workingImg;
	Location center;
};

