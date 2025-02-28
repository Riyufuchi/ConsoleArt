//==============================================================================
// File       : ButtonBuilder.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ButtonBuilder.h"

namespace ConsoleArt {

ButtonBuilder::ButtonBuilder(SDL_Renderer* renderer)
{
	IDs[ButtonType::LOAD] = {"1", "1H"};
	IDs[ButtonType::EXIT] = {"2", "2H"};
	IDs[ButtonType::SETTINGS] = {"3", "3H"};
	IDs[ButtonType::LOAD_ALL] = {"4", "4H"};
	IDs[ButtonType::SELECT_IMAGE] = {"5", "5H"};
	IDs[ButtonType::EDIT_IMAGE] = {"6", "6H"};
	IDs[ButtonType::ABOUT] = {"7", "7H"};
	IDs[ButtonType::BACK] = {"8", "8H"};
	this->buttonSheet = new SpriteSheetSDL("ui.png", renderer);
	if (!buttonSheet)
		return;
	prepareTextures();
}

void ButtonBuilder::prepareTextures()
{
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::LOAD], 0, 0, rectangle);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::EXIT], 0, 160, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::SETTINGS], 0, 96, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::SELECT_IMAGE], 0, 32, rectangle);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::LOAD_ALL], 128, 0, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::EDIT_IMAGE], 128, 32, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::ABOUT], 128, 64, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::BACK], 0, 128, square);
}

std::pair<SDL_Texture*, SDL_Texture*> ButtonBuilder::getButtonTextureFor(ButtonType buttonType)
{
	return buttonSheet->getTexturePair(IDs[buttonType]);
}

ButtonBuilder::~ButtonBuilder()
{
	if (buttonSheet)
		delete buttonSheet;
}

} /* namespace ConsoleArt */
