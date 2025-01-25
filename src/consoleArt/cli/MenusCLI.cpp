//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 28.12.2023
// Last Edit   : Jan 20, 2025
//============================================================================
#include "MenusCLI.h"

namespace ConsoleArt
{
MenusCLI::MenusCLI(ConsoleLib::IConsole* console) : console(console)
{
	menus =
	{
		{ "Load image", "Load all images", "Select image", "List images", "Settings", "About", "Exit"},
		{ "BASIC - █#@%=+:-. ", "PRECISE", "DETAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█",
			"BASIC_INVERTED", "PRECISE_INVERTED", "SHADES", "SHADES_INVERTED", "Back" },
		{ "Classic", "Classic colored", "Pixel colored", "To text file", "Reconvert", "Back to main menu"}
	};
}
int MenusCLI::handleMenu(int menu)
{
	return ConsoleLib::ConsoleUtils::basicMenu(menus[menu]);
}
void MenusCLI::printMainMenu()
{
	console->defaultTextColor();
	const int LENGHT = menus[0].size();
	for(int i = 0; i < LENGHT; i++)
	{
		printf("%d. %s \n", i + 1, menus[0][i]);
	}
	console->resetTextColor();
}
int MenusCLI::invokeMenu(Menu menu)
{
	console->defaultTextColor();
	switch (menu)
	{
		case CHAR_SET_SELECTION: choice = handleMenu(menu); break;
		case PRINT_OPTIONS: choice = handleMenu(menu); break;
		case MAIN_MENU: choice = handleMenu((int)menu); break;
		case COLOR_PICKER: confConsoleTextColor(); break;
		default: choice = -1;
	}
	console->resetTextColor();
	return choice;
}
void MenusCLI::confConsoleTextColor()
{
	if (ConsoleLib::ConsoleUtils::yesNo("Select color [Y/n]: "))
	{
		int max = ConsoleLib::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			console->defaultTextColor();
			std::cout << i + 1 << ". ";
			console->out(ConsoleLib::ColorUtils::getColor(static_cast<ConsoleLib::ColorPallete>(i)), ConsoleLib::ColorUtils::colorPaletteNames[i]);
			std::cout << "\n";
		}
		console->setDefaultTextColor(ConsoleLib::ColorUtils::getColor(static_cast<ConsoleLib::ColorPallete>(ConsoleLib::ConsoleUtils::getIntSafe(1, max) - 1)));
	}
	else if(ConsoleLib::ConsoleUtils::yesNo("Custom color [Y/n]: "))
	{
		console->setDefaultTextColor(colorPicker());
	}
}
void MenusCLI::displayImageInfo(Images::Image& image)
{
	console->defaultTextColor();
	ImageUtils::ImageToolsCLI::displayImageInfo(&image);
	console->resetTextColor();

}
// Menus
int MenusCLI::charSetMenu()
{
	return -1;
}
int MenusCLI::actionMenu()
{
	return -1;
}
int MenusCLI::printMenu()
{
	return -1;
}
ConsoleLib::Color MenusCLI::colorPicker()
{
	std::cout << "Red: ";
	int red = ConsoleLib::ConsoleUtils::getIntSafe(0, 255);
	std::cout << "Green: ";
	int green = ConsoleLib::ConsoleUtils::getIntSafe(0, 255);
	std::cout << "Blue: ";
	int blue = ConsoleLib::ConsoleUtils::getIntSafe(0, 255);
	return ConsoleLib::ColorUtils::newColor(red, green, blue);
}
void MenusCLI::setConsole(ConsoleLib::IConsole* console2)
{
	this->console = console2;
}
MenusCLI::~MenusCLI()
{
}
} // Namespace ConsoleArt
