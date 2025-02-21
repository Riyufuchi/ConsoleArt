//==============================================================================
// File       : Button.h
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_UTILS_BUTTON_H_
#define CONSOLEART_GUI_UTILS_BUTTON_H_

#include <SDL2/SDL.h>

#include "ComponentSDL.h"

namespace ConsoleArt
{
class ButtonSDL : public ComponentSDL
{
private:
	SDL_Color hoverColor;
public:
	ButtonSDL(int x, int y, int width, int height);
	~ButtonSDL();
	virtual void draw(SDL_Renderer* renderer) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_UTILS_BUTTON_H_ */
