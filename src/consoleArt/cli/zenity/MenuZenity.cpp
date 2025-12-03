//==============================================================================
// File       : MenuZenity.cpp
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "MenuZenity.h"

namespace consoleart
{
MenuZenity::MenuZenity(consolelib::IConsole* console, std::function<void()> function) : MenuCLI(console),
	mainMenu(*console, menus.at(Menu::MAIN_MENU), function),
	editImageOptionsMenu(*console, menus.at(Menu::IMAGE_ACTION_OPTIONS), function)
{
}
MenuZenity::~MenuZenity()
{
}
int MenuZenity::mainMenuOptions()
{
	return mainMenu.runMenuLoop();
}
int MenuZenity::createZenityMenu(std::vector<std::string>& menu)
{
	std::ostringstream cmd;
	cmd << "zenity --list --title='Select option' --width=600 --height=400 --column='Filter name' ";

	for (const std::string& f : menu)
	{
		cmd << "'"<< f << "' ";
	}

	FILE *pipe = popen(cmd.str().c_str(), "r");
	if (!pipe)
	{
		std::cerr << "Failed to open Zenity list dialog!" << std::endl;
		return -2;
	}

	char buffer[256]; // Store selected filename
	if (fgets(buffer, sizeof(buffer), pipe) == nullptr)
	{
		pclose(pipe);
		return -1; // No selection (canceled)
	}
	pclose(pipe);

	std::string selectionResult(buffer);
	selectionResult = selectionResult.substr(0, selectionResult.length() - 1); // Removes '\n'
	int i = 0;
	for (const std::string& f : menu)
	{
		if (f == selectionResult)
			return i;
		i++;
	}
	return -3;
}
consolelib::Color MenuZenity::colorPicker()
{
	consolelib::Color color{ -1, 158, 150 };
	FILE *pipe = popen("zenity --color-selection --show-palette --title='Pick a color' --width=600 --height=400", "r");
	if (!pipe)
	{
		std::cerr << "Failed to open Zenity color picker!" << std::endl;
		MenuCLI::confConsoleTextColor();
		return color;
	}

	char buffer[16]; // Enough for "#RRGGBB"
	if (fgets(buffer, sizeof(buffer), pipe) == nullptr)
	{
		std::cerr << "No color selected!" << std::endl;
		pclose(pipe);
		MenuCLI::confConsoleTextColor();
		return color;
	}

	pclose(pipe);

	// Convert "#RRGGBB" to RGB values
	int r, g, b;
	if (sscanf(buffer, "rgb(%d,%d,%d)", &r, &g, &b) == 3)
	{
		return consolelib::Color { (short int) r, (short int) g, (short int) b };
	}

	std::cerr << "Invalid color format: " << buffer << std::endl;
	return color;
}

void MenuZenity::confConsoleTextColor()
{
	consolelib::Color c = colorPicker();
	if (c.red != -1)
		console->setDefaultTextColor(c);
}

int MenuZenity::imageFilterOptions()
{
	int i = createZenityMenu(menus[Menu::FILTERS]);
	if (i == -2)
		return MenuCLI::imageEditOptions();
	return i;

}

int MenuZenity::charSetMenu()
{
	int i = createZenityMenu(menus[Menu::CHAR_SET_SELECTION]);
	if (i == -2)
		return MenuCLI::charSetMenu();
	return i;
}

int MenuZenity::printMenu()
{
	int i = createZenityMenu(menus[Menu::PRINT_OPTIONS]);
	if (i == -2)
		return MenuCLI::printMenu();
	return i;
}

int MenuZenity::imageEditOptions()
{
	return editImageOptionsMenu.runMenuLoop();
}

} /* namespace consoleart */
