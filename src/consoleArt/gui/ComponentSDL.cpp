//==============================================================================
// File       : ComponentSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ComponentSDL.h"

namespace ConsoleArt
{

ComponentSDL::ComponentSDL(int x, int y, int width, int height, SDL_Color baseColor) : mouseOver(false),baseColor(baseColor), rect({x, y, width, height})
{
}

ComponentSDL::~ComponentSDL()
{
}

bool ComponentSDL::isMouseInside(int mouseX, int mouseY) const
{
	return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

void ComponentSDL::setX(int x)
{
	this->rect.x = x;
}

void ComponentSDL::setY(int y)
{
	this->rect.y = y;
}

void ComponentSDL::setWidth(int width)
{
	this->rect.w = width;
}

void ComponentSDL::setHeight(int height)
{
	this->rect.h = height;
}

void ComponentSDL::setMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

int ComponentSDL::getX() const
{
	return this->rect.x;
}

int ComponentSDL::getY() const
{
	return this->rect.y;
}

int ComponentSDL::getWidth() const
{
	return this->rect.w;
}

int ComponentSDL::getHeight() const
{
	return this->rect.h;
}

bool ComponentSDL::isMouseOver() const
{
	return mouseOver;
}

} /* namespace ConsoleArt */
