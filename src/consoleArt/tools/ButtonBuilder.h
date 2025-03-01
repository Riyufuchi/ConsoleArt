//==============================================================================
// File       : ButtonBuilder.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_TOOLS_BUTTONBUILDER_H_
#define CONSOLEART_TOOLS_BUTTONBUILDER_H_

#include <unordered_map>
#include <string>

#include "../../sdl/assets/SpriteSheetSDL.h"

namespace ConsoleArt
{
enum class ButtonType
{
	LOAD,
	LOAD_ALL,
	EDIT_IMAGE,
	EXIT,
	SETTINGS,
	ABOUT,
	BACK,
	SELECT_IMAGE,
	CONVER_TO_ASCII,
	IMAGE_FILTER,
	SHOW_IMAGE
};
class ButtonBuilder
{
private:
	const std::pair<int, int> SQUARE{32, 32};
	const std::pair<int, int> RECTANGLE{64, 32};
	std::unordered_map<ButtonType, std::pair<std::string, std::string>> IDs;
	sdl::SpriteSheetSDL* buttonSheet;
	sdl::SpriteSheetSDL* buttonSheetSmall;
	void logButton(int x, int y, ButtonType type, const std::pair<int, int>& size);
public:
	ButtonBuilder(SDL_Renderer* renderer);
	virtual ~ButtonBuilder();
	std::pair<SDL_Texture*, SDL_Texture*> getButtonTextureFor(ButtonType buttonType, bool small);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_TOOLS_BUTTONBUILDER_H_ */
