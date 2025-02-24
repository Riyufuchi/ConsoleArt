//==============================================================================
// File       : MenuZenity.cpp
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Feb 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MenuZenity.h"

namespace ConsoleArt
{
MenuZenity::MenuZenity(ConsoleLib::IConsole* console) : MenusCLI(console)
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
		MenusCLI::confConsoleTextColor();
		return color;
	}

	char buffer[16]; // Enough for "#RRGGBB"
	if (fgets(buffer, sizeof(buffer), pipe) == nullptr)
	{
		std::cerr << "No color selected!" << std::endl;
		pclose(pipe);
		MenusCLI::confConsoleTextColor();
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

} /* namespace ConsoleArt */
