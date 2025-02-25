//==============================================================================
// File       : Button.cpp
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Feb 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageButtonSDL.h"

namespace ConsoleArt
{

ImageButtonSDL::ImageButtonSDL(int x, int y, int width, int height, SDL_Texture* texture, SDL_Texture* textureHover, std::function<void()> callback) : ComponentSDL(x, y, width, height, callback)
{
	this->texture = texture;
	this->textureHover = textureHover;
}
ImageButtonSDL::ImageButtonSDL(int x, int y, int width, int height, std::pair<SDL_Texture*, SDL_Texture*> texturePair, std::function<void()> callback) : ImageButtonSDL(x, y, width, height, texturePair.first, texturePair.second, callback)
{
}
ImageButtonSDL::~ImageButtonSDL()
{
}
void ImageButtonSDL::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, (mouseOver ? textureHover : texture), nullptr, &rect);
}
} /* namespace ConsoleArt */
