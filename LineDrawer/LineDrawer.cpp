#include "stdafx.h"
#include "LineDrawer.h"
#include <cstdlib>
#include <ctime>

LineDrawer::LineDrawer(SDLRenderer & renderer, SDLSurface & referenceImg) : renderer(renderer), referenceImg(referenceImg)
{
	workingImg = new SDLSurface(referenceImg);
	srand(time(NULL));
}

LineDrawer::~LineDrawer()
{

}

void LineDrawer::init()
{
	renderer.setLogicalSize(referenceImg.getWidth(), referenceImg.getHeight());
}

SDLSurface* LineDrawer::update()
{
	int width = workingImg->getWidth();
	int height = workingImg->getHeight();

	int x = rand() % width;
	int y = rand() % height;

	Location location{ x, y };
	Colour colour{ 255, 255, 255 };

	workingImg->setPixel(location, colour);

	return workingImg;
}

std::vector<Pixel> LineDrawer::getLinePoints(Location p1, Location p2)
{
	return std::vector<Pixel>();
}
