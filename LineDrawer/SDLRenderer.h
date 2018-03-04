#pragma once
#include "Renderer.h"
#include "stdafx.h"
class SDLRenderer :
	public Renderer
{
public:
	SDLRenderer();
	~SDLRenderer();
	SDL_Surface* getScreenSurface();
	SDL_Renderer* getRenderer();
private:
	SDL_Window*		window			= NULL;
	SDL_Surface*	screenSurface	= NULL;
	SDL_Renderer*	renderer		= NULL;
};

