//==============================================================================
// File       : StringPrinter.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_ASSETS_STRINGPRINTER_H_
#define CONSOLEART_GUI_ASSETS_STRINGPRINTER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace ConsoleArt
{
class StringPrinter //TODO: Optimize this class to be something like StringSDL
{
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
public:
	StringPrinter(SDL_Renderer* renderer, std::string fontname, int size);
	virtual ~StringPrinter();
	SDL_Texture* renderText(SDL_Renderer* renderer, std::string text, SDL_Color color);
	void renderTextAt(int x, int y, std::string text, SDL_Color color);
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_ASSETS_STRINGPRINTER_H_ */
