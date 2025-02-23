//==============================================================================
// File       : Button.h
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_UTILS_IMAGE_BUTTON_H_
#define CONSOLEART_GUI_UTILS_IMAGE_BUTTON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../abstract/ComponentSDL.h"

namespace ConsoleArt
{
class ImageButtonSDL : public ComponentSDL
{
private:
	SDL_Texture* texture;
	SDL_Texture* textureHover;
public:
	ImageButtonSDL(int x, int y, int width, int height, SDL_Texture* texture, SDL_Texture* textureHover);
	~ImageButtonSDL();
	virtual void draw(SDL_Renderer* renderer) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_UTILS_BUTTON_H_ */
