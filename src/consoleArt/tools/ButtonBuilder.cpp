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
	/*IDs[ButtonType::LOAD] = {"1", "1H"};
	IDs[ButtonType::EXIT] = {"2", "2H"};
	IDs[ButtonType::SETTINGS] = {"3", "3H"};
	IDs[ButtonType::LOAD_ALL] = {"4", "4H"};
	IDs[ButtonType::SELECT_IMAGE] = {"5", "5H"};
	IDs[ButtonType::EDIT_IMAGE] = {"6", "6H"};
	IDs[ButtonType::ABOUT] = {"7", "7H"};
	IDs[ButtonType::BACK] = {"8", "8H"};*/
	this->buttonSheet = new SpriteSheetSDL("ui_big.png", renderer);
	this->buttonSheetSmall = new SpriteSheetSDL("ui_small.png", renderer);
	if (!buttonSheet || !buttonSheetSmall)
		return;
	// BigButtons
	logButton(0, 0, ButtonType::LOAD, RECTANGLE);
	logButton(0, 1, ButtonType::SELECT_IMAGE, RECTANGLE);
	logButton(1, 0, ButtonType::IMAGE_FILTER, RECTANGLE);
	logButton(2, 0, ButtonType::CONVER_TO_ASCII, RECTANGLE);
	// SmallButtons
	logButton(0, 0, ButtonType::SETTINGS, SQUARE);
	logButton(0, 1, ButtonType::BACK, SQUARE);
	logButton(0, 2, ButtonType::EXIT, SQUARE);
	logButton(1, 1, ButtonType::LOAD_ALL, SQUARE);
	logButton(1, 2, ButtonType::EDIT_IMAGE, SQUARE);
	logButton(1, 3, ButtonType::ABOUT, SQUARE);
}

void ButtonBuilder::logButton(int x, int y, ButtonType type, const std::pair<int, int>& size)
{
	std::string ID = std::to_string((int)type);
	IDs[type] = { ID, ID + "H" };
	switch (size.first)
	{
		case 32: this->buttonSheetSmall->prepareTexturePair(IDs[type], x * size.first * 2, y * size.second, size); break;
		case 64: this->buttonSheet->prepareTexturePair(IDs[type], x * size.first * 2, y * size.second, size); break;
	}
}

void ButtonBuilder::prepareTextures()
{
	/*this->buttonSheet->prepareTexturePair(IDs[ButtonType::LOAD], 0, 0, rectangle);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::EXIT], 0, 160, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::SETTINGS], 0, 96, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::SELECT_IMAGE], 0, 32, rectangle);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::LOAD_ALL], 128, 0, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::EDIT_IMAGE], 128, 32, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::ABOUT], 128, 64, square);
	this->buttonSheet->prepareTexturePair(IDs[ButtonType::BACK], 0, 128, square);*/
}

std::pair<SDL_Texture*, SDL_Texture*> ButtonBuilder::getButtonTextureFor(ButtonType buttonType, bool small)
{
	if (small)
		return buttonSheetSmall->getTexturePair(IDs[buttonType]);
	return buttonSheet->getTexturePair(IDs[buttonType]);
}

ButtonBuilder::~ButtonBuilder()
{
	if (buttonSheet)
		delete buttonSheet;
}

} /* namespace ConsoleArt */
