//==============================================================================
// File       : StringButtonSDL.h
// Author     : riyufuchi
// Created on : Mar 4, 2025
// Last edit  : Mar 4, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef SDL_COMPONENTS_STRINGBUTTONSDL_H_
#define SDL_COMPONENTS_STRINGBUTTONSDL_H_

#include "../abstract/ComponentSDL.h"
#include "../assets/StringSDL.h"

namespace sdl
{
class StringButtonSDL : public ComponentSDL
{
private:
	StringSDL* text;
	StringSDL* textHover;
public:
	StringButtonSDL(int x, int y, StringSDL* text, SDL_Color hoverColor, std::function<void()> callback = nullptr);
	virtual ~StringButtonSDL();
	virtual void draw(SDL_Renderer *renderer) override;
};
} /* namespace sdl */
#endif /* SDL_COMPONENTS_STRINGBUTTONSDL_H_ */
