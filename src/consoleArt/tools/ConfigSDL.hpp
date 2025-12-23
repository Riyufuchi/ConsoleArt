//==============================================================================
// File       : ConfigSDL.hpp
// Author     : riyufuchi
// Created on : May 25, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef _CONSOLE_ART_CONFIG_SDL_HPP_
#define _CONSOLE_ART_CONFIG_SDL_HPP_

#include <SDL2/SDL.h>
#include <string>

namespace consoleart
{
	inline const std::string FONT_BASE = "assets/fonts/TF2Build.ttf";
	inline const std::string FONT_SECONDARY = "assets/fonts/TF2secondary.ttf";
	inline const std::string FONT_PROF = "assets/fonts/TF2professor.ttf";
	inline const SDL_Color BASE_TEXT_COLOR = {255, 105, 180, 255};
	inline const SDL_Color HOVER_TEXT_COLOR = {255, 179, 222, 255};
}

#endif
