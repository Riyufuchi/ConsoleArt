//==============================================================================
// File       : StringPrinter.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "StringPrinter.h"

namespace ConsoleArt {

StringPrinter::StringPrinter(SDL_Renderer* renderer, std::string fontname, int size) : renderer(renderer), font(TTF_OpenFont(fontname.c_str(), size))
{
	if (!font)
	{
		SDL_Log("ERROR: Failed to load font: %s", TTF_GetError());
	}
}

StringPrinter::~StringPrinter()
{
	TTF_CloseFont(font);
}

void StringPrinter::renderTextAt(int x, int y, std::string text, SDL_Color color)
{
	SDL_Rect dstRect;
	SDL_Texture* textTexture = renderText(renderer, text, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &dstRect.w, &dstRect.h);
	dstRect.x = x;
	dstRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
	SDL_DestroyTexture(textTexture);
}

SDL_Texture* StringPrinter::renderText(SDL_Renderer* renderer, std::string text, SDL_Color color)
{
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!textSurface)
	{
		SDL_Log("ERROR: Failed to create text surface: %s", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (!textTexture)
	{
		SDL_Log("ERROR: Failed to create texture from text: %s", SDL_GetError());
	}

	return textTexture;
}

} /* namespace ConsoleArt */
