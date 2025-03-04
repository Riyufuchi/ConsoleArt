//==============================================================================
// File       : StringButtonSDL.cpp
// Author     : riyufuchi
// Created on : Mar 4, 2025
// Last edit  : Mar 4, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "StringButtonSDL.h"

namespace sdl
{
StringButtonSDL::StringButtonSDL(int x, int y, StringSDL* text, StringSDL* textHover, std::function<void()> callback) : ComponentSDL(x, y, 10, 10, callback), text(text), textHover(textHover)
{
	this->rect.w = text->getWidth();
	this->rect.h = text->getHeight();
}

StringButtonSDL::~StringButtonSDL()
{
	delete text;
	delete textHover;
}

void StringButtonSDL::draw(SDL_Renderer *renderer)
{
	if (isMouseOver())
		textHover->draw();
	else
		text->draw();
}

void StringButtonSDL::setY(int y)
{
	ComponentSDL::setY(y);
	text->setY(y);
	textHover->setY(y);
}

void StringButtonSDL::setX(int x)
{
	ComponentSDL::setX(x);
	text->setX(x);
	textHover->setX(x);
}

} /* namespace sdl */
