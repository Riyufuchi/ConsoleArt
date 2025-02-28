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

#include "../sdl/assets/SpriteSheetSDL.h"

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
	SELECT_IMAGE
};
class ButtonBuilder
{
private:
	const std::pair<int, int> square{32, 32};
	const std::pair<int, int> rectangle{64, 32};
	std::unordered_map<ButtonType, std::pair<std::string, std::string>> IDs;
	SpriteSheetSDL* buttonSheet;
	void prepareTextures();
public:
	ButtonBuilder(SDL_Renderer* renderer);
	virtual ~ButtonBuilder();
	std::pair<SDL_Texture*, SDL_Texture*> getButtonTextureFor(ButtonType buttonType);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_TOOLS_BUTTONBUILDER_H_ */
