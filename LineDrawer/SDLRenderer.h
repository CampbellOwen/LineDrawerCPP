#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "SDLSurface.h"

class SDLRenderer :
	public Renderer
{
public:
	SDLRenderer();
	~SDLRenderer();
	SDL_Surface* getScreenSurface();
	SDL_Renderer* getRenderer();
	void Render(SDLSurface & surface);
	void setLogicalSize(int w, int h);
private:
	SDL_Window*		window			= NULL;
	SDL_Surface*	screenSurface	= NULL;
	SDL_Renderer*	renderer		= NULL;
};

