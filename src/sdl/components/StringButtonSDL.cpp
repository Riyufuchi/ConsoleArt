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
StringButtonSDL::StringButtonSDL(int x, int y, StringSDL* text, SDL_Color hoverColor, std::function<void()> callback) : ComponentSDL(x, y, 10, 10, callback), text(text)
{
	this->rect.w = text->getWidth();
	this->rect.h = text->getHeight();
	this->textHover = new sdl::StringSDL(text->getText(), text->getFont(), text->getSize(), hoverColor, text->getRenderer());
}

StringButtonSDL::~StringButtonSDL()
{
	delete text;
	delete textHover;
}

void StringButtonSDL::draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, isMouseOver() ? textHover->getTexture() : text->getTexture(), nullptr, &rect);
}

} /* namespace sdl */
