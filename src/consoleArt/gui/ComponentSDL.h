//==============================================================================
// File       : ComponentSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_COMPONENTSDL_H_
#define CONSOLEART_GUI_COMPONENTSDL_H_

#include <SDL2/SDL.h>

namespace ConsoleArt
{
class ComponentSDL
{
protected:
	bool mouseOver;
	SDL_Color baseColor;
	SDL_Rect rect;
public:
	ComponentSDL(int x, int y, int width, int height, SDL_Color baseColor);
	virtual ~ComponentSDL();
	// Functions
	bool isMouseInside(int x, int y) const;
	//Methods
	virtual void draw(SDL_Renderer* renderer) = 0;
	// Setters
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setMouseOver(bool mouseOver);
	// Getters
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	bool isMouseOver() const;
};
} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_COMPONENTSDL_H_ */
