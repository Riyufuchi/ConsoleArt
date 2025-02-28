//==============================================================================
// File       : ContentPanelSDL.cpp
// Author     : riyufuchi
// Created on : Feb 23, 2025
// Last edit  : Feb 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ContentPanelSDL.h"

namespace sdl
{
ContentPanelSDL::ContentPanelSDL(int x, int y) : ComponentSDL(x, y, 10, 10)
{
}

ContentPanelSDL::~ContentPanelSDL()
{
	for (size_t yc = 0; yc < componentsAtY.size(); yc++)
	{
		for (ComponentSDL* component : componentsAtY[yc])
		{
			delete component;
		}
	}
}

void ContentPanelSDL::draw(SDL_Renderer* renderer)
{
	for (size_t yc = 0; yc < componentsAtY.size(); yc++)
		for (ComponentSDL*& component : componentsAtY[yc])
			component->draw(renderer);
}

void ContentPanelSDL::checkHoverOverContent(int& x, int& y)
{
	for (size_t yc = 0; yc < componentsAtY.size(); yc++)
	{
		for (ComponentSDL*& component : componentsAtY[yc])
		{
			component->setMouseOver(component->isMouseInside(x, y));
		}
	}
}

void ContentPanelSDL::tickOnClick()
{
	for (size_t yc = 0; yc < componentsAtY.size(); yc++)
	{
		for (ComponentSDL*& component : componentsAtY[yc])
		{
			component->onClick();
		}
	}
}

void ContentPanelSDL::reposeContent()
{
	for (size_t y = 0; y < componentsAtY.size(); y++)
	{
		widthAtY[y] = rect.x;
		for (ComponentSDL*& component : componentsAtY[y])
		{
			component->setX(widthAtY[y]);
			widthAtY[y] += component->getWidth();
			component->setY((y * component->getHeight()) + rect.y);
		}
	}
}

void ContentPanelSDL::addComponent(int y, ComponentSDL* component)
{
	if (component == nullptr || y < 0)
		return;

	if (componentsAtY.size() < (long unsigned int)y)
		componentsAtY[y] = { component };
	else
		componentsAtY[y].emplace_back(component);

	if (widthAtY.size() < (long unsigned int)y)
		widthAtY[y] = rect.x;
	component->setX(widthAtY[y]);
	widthAtY[y] += component->getWidth();
	component->setY((y * component->getHeight()) + rect.y);
	rect.w = std::max(rect.w, component->getX() + component->getWidth());
	rect.h = std::max(rect.h, component->getY() + component->getHeight());
}

} /* namespace ConsoleArt */
