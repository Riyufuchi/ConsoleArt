//==============================================================================
// File       : ButtonBuilder.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Dec 03, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/tools/ButtonBuilder.h"

namespace consoleart
{
ButtonBuilder::ButtonBuilder(SDL_Renderer* renderer)
{
	this->buttonSheet = new sdl::SpriteSheetSDL(ui_big_png_len, ui_big_png, renderer);
	this->buttonSheetSmall = new sdl::SpriteSheetSDL(ui_small_png_len, ui_small_png, renderer);

	if (!buttonSheet)
	{
		std::cerr << "No Sheet 1";
	}

	if (!buttonSheetSmall)
	{
		std::cerr << "No Sheet 2";
	}

	// Big Buttons
	logButton(0, 0, ButtonType::LOAD, RECTANGLE);
	logButton(0, 1, ButtonType::SELECT_IMAGE, RECTANGLE);
	logButton(0, 2, ButtonType::EXIT, RECTANGLE);
	logButton(0, 3, ButtonType::BACK, RECTANGLE);
	logButton(0, 4, ButtonType::WATERMARK, RECTANGLE);
	logButton(0, 5, ButtonType::EXPORT_AS, RECTANGLE);
	// X = 1
	logButton(1, 0, ButtonType::IMAGE_FILTER, RECTANGLE);
	// X = 2
	logButton(2, 0, ButtonType::CONVER_TO_ASCII, RECTANGLE);
	// Small Buttons
	logButton(0, 0, ButtonType::SETTINGS, SQUARE);
	logButton(0, 1, ButtonType::BACK, SQUARE);
	logButton(0, 2, ButtonType::EXIT, SQUARE);
	logButton(0, 3, ButtonType::APPLY, SQUARE);
	logButton(0, 4, ButtonType::SHOW_IMAGE, SQUARE);
	logButton(0, 5, ButtonType::SELECT, SQUARE);
	// X = 1
	logButton(1, 1, ButtonType::LOAD_ALL, SQUARE);
	logButton(1, 2, ButtonType::EDIT_IMAGE, SQUARE);
	logButton(1, 3, ButtonType::ABOUT, SQUARE);
	logButton(1, 4, ButtonType::IMAGE_INFO, SQUARE);
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

std::pair<SDL_Texture*, SDL_Texture*> ButtonBuilder::getButtonTextureFor(ButtonType buttonType, bool isSquareButton)
{
	if (isSquareButton)
		return buttonSheetSmall->getTexturePair(IDs[buttonType]);
	return buttonSheet->getTexturePair(IDs[buttonType]);
}

ButtonBuilder::~ButtonBuilder()
{
	if (buttonSheet)
	{
		delete buttonSheet;
		buttonSheet = nullptr;
	}
	if (buttonSheetSmall)
	{
		delete buttonSheetSmall;
		buttonSheetSmall = nullptr;
	}
}

bool ButtonBuilder::isReady() const
{
	return buttonSheet->isReady() && buttonSheetSmall->isReady();
}

} /* namespace consoleart */
