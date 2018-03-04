#pragma once
#include "Renderer.h"
#include "stdafx.h"
class SDLRenderer :
	public Renderer
{
public:
	SDLRenderer();
	~SDLRenderer();
	void loadImage( std::string path );
	void draw();
private:
	SDL_Window*		window			= NULL;
	SDL_Surface*	screenSurface	= NULL;
	SDL_Surface*	imgSurface		= NULL;
	SDL_Renderer*	renderer		= NULL;

};

