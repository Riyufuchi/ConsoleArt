//==============================================================================
// File       : MenuZenity.cpp
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MenuZenity.h"

namespace ConsoleArt
{
MenuZenity::MenuZenity(ConsoleLib::IConsole* console) : MenuCLI(console)
{
}
MenuZenity::~MenuZenity()
{
}
ConsoleLib::Color MenuZenity::colorPicker()
{
	ConsoleLib::Color color{ -1, 158, 150 };
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
		return ConsoleLib::Color { (short int) r, (short int) g, (short int) b };
	}

	std::cerr << "Invalid color format: " << buffer << std::endl;
	return color;
}

void MenuZenity::confConsoleTextColor()
{
	ConsoleLib::Color c = colorPicker();
	if (c.red != -1)
		console->setDefaultTextColor(c);
}

int MenuZenity::imageFilterOptions()
{
	std::ostringstream cmd;
	cmd << "zenity --list --title='Select filter' --width=600 --height=400 --column='Filter name' ";

	for (const std::string& f : menus[Menu::FILTERS])
	{
		cmd << "'"<< f << "' ";
	}

	FILE *pipe = popen(cmd.str().c_str(), "r");
	if (!pipe)
	{
		std::cerr << "Failed to open Zenity list dialog!" << std::endl;
		return MenuCLI::imageFilterOptions();
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
	for (const std::string& f : menus[Menu::FILTERS])
	{
		if (f == selectionResult)
			return i;
		i++;
	}
	return -2;
}

} /* namespace ConsoleArt */
