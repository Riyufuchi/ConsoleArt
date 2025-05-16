//==============================================================================
// File       : MenuTFD.cpp
// Author     : riyufuchi
// Created on : May 16, 2025
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MenuTFD.h"

namespace ConsoleArt
{
MenuTFD::MenuTFD(ConsoleLib::IConsole* console, std::function<void()> function) : MenuCLI(console), mainMenu(*console, menus.at(Menu::MAIN_MENU), function)
{}

int MenuTFD::mainMenuOptions()
{
	return mainMenu.runMenuLoop();
}

ConsoleLib::Color MenuTFD::colorPicker()
{
	unsigned char rgb[3] = {255, 255, 255};
	const char* hex = tinyfd_colorChooser("Select a color", "#FFFFFF", rgb, rgb);
	if (hex)
	{
		return ConsoleLib::Color{rgb[0], rgb[1], rgb[2]};
	}

	return ConsoleLib::ColorUtils::getColor(ConsoleLib::CONSOLE_ART_UNIX_DEFAULT);
}

void MenuTFD::confConsoleTextColor()
{
	console->setDefaultTextColor(colorPicker());
}

} /* namespace ConsoleLib */
