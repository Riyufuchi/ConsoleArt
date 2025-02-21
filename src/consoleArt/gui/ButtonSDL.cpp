//==============================================================================
// File       : Button.cpp
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ButtonSDL.h"

namespace ConsoleArt {

ButtonSDL::ButtonSDL(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), hovered(false)
{
	this->baseColor = {0, 128, 255, 255};
	this->hoverColor = {0, 200, 255, 255};
	this->rect = {x, y, width, height};
}
ButtonSDL::~ButtonSDL()
{
}

void ButtonSDL::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer,
		hovered ? hoverColor.r : baseColor.r,
		hovered ? hoverColor.g : baseColor.g,
		hovered ? hoverColor.b : baseColor.b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void ButtonSDL::setHover(bool hover)
{
	hovered = hover;
}
bool ButtonSDL::getHover()
{
	return hovered;
}

int ButtonSDL::getHeight() const {
	return height;
}

void ButtonSDL::setHeight(int height) {
	this->height = height;
}

int ButtonSDL::getWidth() const {
	return width;
}

void ButtonSDL::setWidth(int width) {
	this->width = width;
}

int ButtonSDL::getX() const
{
	return x;
}

void ButtonSDL::setX(int x)
{
	this->x = x;
	this->rect.x = x;
}

int ButtonSDL::getY() const
{
	return y;
}

void ButtonSDL::setY(int y)
{
	this->y = y;
	this->rect.y = y;
}

bool ButtonSDL::isMouseInside(int mouseX, int mouseY)
{
	return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}
} /* namespace ConsoleArt */
