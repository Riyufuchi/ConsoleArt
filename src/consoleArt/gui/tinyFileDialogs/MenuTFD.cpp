//==============================================================================
// File       : MenuTFD.cpp
// Author     : riyufuchi
// Created on : May 16, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "MenuTFD.h"

namespace consoleart
{
MenuTFD::MenuTFD(consolelib::IConsole* console, std::function<void()> function) : MenuCLI(console), mainMenu(*console, menus.at(Menu::MAIN_MENU), function)
{}

int MenuTFD::mainMenuOptions()
{
	return mainMenu.runMenuLoop();
}

consolelib::Color MenuTFD::colorPicker()
{
	unsigned char rgb[3] = {255, 255, 255};
	const char* hex = tinyfd_colorChooser("Select a color", "#FFFFFF", rgb, rgb);
	if (hex)
	{
		return consolelib::Color{rgb[0], rgb[1], rgb[2]};
	}

	return consolelib::color_tools::getColor(consolelib::CONSOLE_ART_UNIX_DEFAULT);
}

void MenuTFD::confConsoleTextColor()
{
	console->setDefaultTextColor(colorPicker());
}

} /* namespace consolelib */
