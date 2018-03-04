#pragma once
#include "stdafx.h"
class Renderer {
public:
	virtual void loadImage(std::string path) = 0;
	virtual void draw() = 0;
	virtual ~Renderer() = 0;
};
