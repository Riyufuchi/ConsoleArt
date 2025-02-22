//==============================================================================
// File       : Button.cpp
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageButtonSDL.h"

namespace ConsoleArt
{

ImageButtonSDL::ImageButtonSDL(int x, int y, int width, int height, SDL_Texture* texture, SDL_Texture* textureHover) : ComponentSDL(x, y, width, height, {0, 128, 255, 255})
{
	this->texture = texture;
	this->textureHover = textureHover;
}
ImageButtonSDL::~ImageButtonSDL()
{
}

void ImageButtonSDL::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, (mouseOver ? textureHover : texture), nullptr, &rect);
}
} /* namespace ConsoleArt */
