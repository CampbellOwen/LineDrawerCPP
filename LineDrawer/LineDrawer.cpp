#include "stdafx.h"
#include "LineDrawer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

LineDrawer::LineDrawer(SDLRenderer & renderer, SDLSurface & referenceImg) : renderer(renderer), referenceImg(referenceImg)
{
	workingImg = new SDLSurface(referenceImg);
	srand(time(NULL));
	palette = referenceImg.getPalette();
	center = Location{ workingImg->getWidth(), workingImg->getHeight() };
}

LineDrawer::~LineDrawer()
{

}

void LineDrawer::init()
{
	renderer.setLogicalSize(referenceImg.getWidth(), referenceImg.getHeight());
	renderer.Render(referenceImg);
}

SDLSurface* LineDrawer::update()
{
	int width = workingImg->getWidth();
	int height = workingImg->getHeight();

	Location p1{ rand() % width, rand() % height };
	Location p2{ rand() % width, rand() % height };

	Colour colour = getRandomColour( false );

	/*std::cout << "Colour: {" << colour.r << ", " << colour.g << ", " << colour.b << "}" << std::endl;*/

	std::vector<Pixel> pixels = getLinePoints(colour, p1, p2);

	if (shouldDrawLine(pixels)) {
		for (int i = 0; i < pixels.size(); i++) {
			workingImg->setPixel(pixels[i].location, pixels[i].colour);
		}
	}

	return workingImg;
}

float LineDrawer::meanSquaredError(Colour c1, Colour c2)
{
	
	float redSquareError = (c1.r * 1.0) - c2.r;
	redSquareError *= redSquareError;
	float greenSquareError = (c1.g * 1.0) - c2.g;
	greenSquareError *= greenSquareError;
	float blueSquareError = (c1.b * 1.0) - c2.b;
	blueSquareError *= blueSquareError;

	return (redSquareError + greenSquareError + blueSquareError) / 3.0f;
}

bool LineDrawer::shouldDrawLine(std::vector<Pixel> line)
{
	float curr_error = 0.0f;
	float new_error = 0.0f;
	for (int i = 0; i < line.size(); i++) {
		Location curr_location = line[i].location;
		curr_error += meanSquaredError( workingImg->getPixel(curr_location).colour, referenceImg.getPixel(curr_location).colour );
		new_error += meanSquaredError(line[i].colour, referenceImg.getPixel(curr_location).colour);
	}

	curr_error /= line.size();
	new_error /= line.size();
	
	return new_error <= curr_error;
}

// Bresenham
std::vector<Pixel> LineDrawer::getLinePoints(Colour colour, Location p1, Location p2)
{
	std::vector<Pixel> pixels;

	
	if (p2.y < p1.y) {
		Location temp = p1;
		p1 = p2;
		p2 = temp;
	}

	int octant = getOctant(p1, p2);

	Location start = toOctantZero(octant, p1);
	Location end = toOctantZero(octant, p2);

	if (start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0) {
		std::cout << "o no" << std::endl;
	}

	int x = start.x;
	int m_num = 2 * (end.y - start.y);
	int y_int = start.y;
	int y_num = (end.x - start.x);
	int y_den = 2 * (end.x - start.x);

	int error = m_num - y_den;

	while (x <= end.x) {

		Location coord = octantZeroTo(octant, Location{ x, y_int });
		pixels.push_back(Pixel{ coord, colour });

		x++;
		if (y_num + error >= 0) {
			y_int++;
			y_num += error;
		}
		else {
			y_num += m_num;
		}
	}


	return pixels;
}

int LineDrawer::getOctant(Location p1, Location p2)
{
	int x = p2.x - p1.x;
	int y = (p2.y - p1.y);
	int octants[2][2][2] = {
		{ { 0, 1}, { 7, 6 } },
		{ { 3, 2}, { 4, 5 } }
	};

	return octants[x < 0][y < 0][abs(x) < abs(y)];
}

Location LineDrawer::toOctantZero(int octant, Location point)
{
	switch (octant) {
	case 0:
		return point;
	case 1:
		return Location{ point.y, point.x };
	case 2:
		return Location{ point.y, center.x - ( point.x - center.x ) };
	case 3:
		return Location{ center.x - (point.x - center.x), point.y };
	case 4:
		return Location{ center.x - (point.x - center.x), center.y - ( point.y - center.y ) };
	case 5:
		return Location{ center.y - (point.y - center.y), center.x - (point.x - center.x) };
	case 6:
		return Location{ center.y - (point.y - center.y), point.x };
	case 7:
		return Location{ point.x, center.y - (point.y - center.y) };
	}
	return point;
}

Location LineDrawer::octantZeroTo(int octant, Location point)
{
	switch (octant) {
	case 0:
		return point;
	case 1:
		return Location{ point.y, point.x };
	case 2:
		return Location{ center.y - (point.y - center.y), point.x };
	case 3:
		return Location{ center.x - (point.x - center.x), point.y };
	case 4:
		return Location{ center.x - (point.x - center.x), center.y - (point.y - center.y) };
	case 5:
		return Location{ center.y - (point.y - center.y), -point.x };
	case 6:
		return Location{ point.y, center.x - (point.x - center.x) };
	case 7:
		return Location{ point.x, center.y - (point.y - center.y) };
	}
	return point;
}

Colour LineDrawer::getRandomColour( bool weighted )
{
	if (weighted) {
		double rand_num = (rand() * 1.0f) / RAND_MAX;
		double total = 0.0f;
		for (auto it : palette) {
			total += it.second;
			if (rand_num <= total) {
				return it.first;
			}
		}
		return Colour{ 0,0,0 };
	}
	else {
		int rand_num = rand() % palette.size();
		int count = 0;
		for (auto it : palette) {
			if (count == rand_num) {
				return it.first;
			}
			count++;
		}
		return Colour{ 0, 0, 0 };
	}
}
