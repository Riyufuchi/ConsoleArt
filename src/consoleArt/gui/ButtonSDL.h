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

namespace ConsoleArt
{
class ButtonSDL
{
private:
	int x;
	int y;
	int width;
	int height;
	bool hovered;
	SDL_Color baseColor;
	SDL_Color hoverColor;
	SDL_Rect rect;
public:
	ButtonSDL(int x, int y, int width, int height);
	~ButtonSDL();
	void draw(SDL_Renderer* renderer);

	bool isMouseInside(int x, int y);

	void setHover(bool hover);
	bool getHover();

	int getHeight() const;
	void setHeight(int height);
	int getWidth() const;
	void setWidth(int width);
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_UTILS_BUTTON_H_ */
