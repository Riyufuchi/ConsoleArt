//==============================================================================
// File       : ConfigSDL.hpp
// Author     : riyufuchi
// Created on : May 25, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLE_ART_CONFIG_SDL_HPP_
#define _CONSOLE_ART_CONFIG_SDL_HPP_

#include <string>

#include "../../sdl/assets/StringSDL.h"

namespace ConsoleArt
{
	inline const std::string FONT_BASE = "assets/TF2Build.ttf";
	inline const std::string FONT_SECONDARY = "assets/TF2secondary.ttf";
	inline const std::string FONT_PROF = "assets/TF2professor.ttf";
	inline const SDL_Color BASE_TEXT_COLOR = {255, 105, 180, 255};
	inline const SDL_Color HOVER_TEXT_COLOR = {255, 179, 222, 255};
}

#endif
