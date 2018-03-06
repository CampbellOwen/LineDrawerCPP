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
private:
	std::vector<Pixel> getLinePoints(Location p1, Location p2);
	SDLRenderer& renderer;
	SDLSurface& referenceImg;
	SDLSurface* workingImg;
};

