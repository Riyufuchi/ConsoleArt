//==============================================================================
// File       : ContentPanelSDL.cpp
// Author     : riyufuchi
// Created on : Feb 23, 2025
// Last edit  : Feb 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ContentPanelSDL.h"

namespace ConsoleArt {

ContentPanelSDL::ContentPanelSDL(int x, int y, int width, int height, int padding) : ComponentSDL(x, y, width, height), padding(padding)
{
}

ContentPanelSDL::~ContentPanelSDL()
{
}

void ContentPanelSDL::draw(SDL_Renderer* renderer)
{
	for (std::pair<const int, std::vector<ConsoleArt::ComponentSDL*>>& row : components)
	{
		for (ComponentSDL* comp : row.second)
		{
			comp->draw(renderer);
		}
	}
}

void ContentPanelSDL::checkHover(int& x, int& y)
{
	for (std::pair<const int, std::vector<ConsoleArt::ComponentSDL*>>& row : components)
		{
			for (ComponentSDL* comp : row.second)
			{
				comp->setMouseOver(comp->isMouseInside(x, y));
			}
		}
}

void ContentPanelSDL::repose()
{
	int offsetX = rect.x;
	int lastY = 0;
	int y = 0;
	int x = 0;
	for (std::pair<const int, std::vector<ConsoleArt::ComponentSDL*>>& row : components)
	{
		lastY = rect.y + x;
		for (ComponentSDL* comp : row.second)
		{
			comp->setY(lastY);
			comp->setX(offsetX);
			offsetX += comp->getWidth() + padding;
			y = comp->getHeight() + padding;
			if (y > x)
				x = y;
		}
		offsetX = rect.x;
	}
}

void ContentPanelSDL::addComponent(int x, int y, ComponentSDL* component)
{
	if (component == nullptr || y < 0)
		return;
	int offsetY = 0;
	if (components.empty())
	{
		component->setX(rect.x);
		SDL_Log("Here\n");
		for (std::pair<const int, std::vector<ConsoleArt::ComponentSDL*>>& row : components)
			if ((int)row.second.size() < x)
				offsetY += row.second.at(x)->getHeight();
		component->setY((int)components.size() * padding + rect.y + offsetY);
		SDL_Log("There\n");
		components[0] = std::vector{ component };
		components[1] = {};
		SDL_Log("Added\n");
	}
	else
	{
		SDL_Log("1 - X: %d, Y: %d, Size: %ld\n", x, y, components.size());
		for (int i = 0; i < y; i++)
		{
			SDL_Log("I: %d\n", i);
			if ((int)components.at(y).size() > x)
				offsetY += components.at(y).at(x)->getHeight();
		}
		SDL_Log("2\n");
		component->setY((int)components.size() * padding + rect.y + offsetY);
		component->setX(rect.x + components.at(y).size() * padding);
		components[y].emplace_back(component);
		components[y+1 ]= {};
		SDL_Log("3\n");
	}
	rect.h += 0;
	int o = 0;
	offsetY = 0;
	rect.w = 0;
	for (std::pair<const int, std::vector<ConsoleArt::ComponentSDL*>>& row : components)
	{
		rect.w = (row.second.size() * padding) - padding;
		rect.h = 0;
		for (ComponentSDL* comp : row.second)
		{
			rect.h += component->getHeight() + padding;
			rect.w += comp->getWidth();
			if (rect.w > offsetY)
				offsetY = rect.w;
		}
		if (rect.h > o)
			o = rect.h;
	}
	rect.w = offsetY;
	rect.h = o;
}

} /* namespace ConsoleArt */
