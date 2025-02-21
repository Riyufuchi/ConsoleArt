//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : Dec 28,2023
// Last Edit   : Feb 21, 2025
//============================================================================
#include "MenusCLI.h"

namespace ConsoleArt
{
MenusCLI::MenusCLI(ConsoleLib::IConsole* console) : console(console)
{
	menus[Menu::MAIN_MENU] = { "Load image", "Load all images", "Select image", "Image actions", "List images", "Settings", "About", "Exit"};
	menus[Menu::CHAR_SET_SELECTION] ={ "BASIC - █#@%=+:-. ", "PRECISE", "DETAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█",
			"BASIC_INVERTED", "PRECISE_INVERTED", "SHADES", "SHADES_INVERTED", "Back" };
	menus[Menu::PRINT_OPTIONS] = { "Classic", "Classic colored", "Pixel colored", "To text file", "Reconvert", "Back to main menu"};
	menus[Menu::IMAGE_ACTION_OPTIONS] = {"Convert to ASCII", "Add signature", "Apply filter"};
	menus[Menu::FILTERS] = {"Matrix", "Purplefier", "Purplefier shading", "Purplefier soft"};
}
int MenusCLI::handleMenu(Menu menu)
{
	return ConsoleLib::ConsoleUtils::basicMenu(menus.at(menu));
}
void MenusCLI::printMainMenu()
{
	console->enableCustomFG();
	std::vector<const char*> & mm = menus.at(MAIN_MENU);
	const int LENGHT = mm.size();
	for(int i = 0; i < LENGHT; i++)
	{
		printf("%d. %s \n", i + 1, mm[i]);
	}
	console->disableCustomFG();
}
int MenusCLI::invokeMenu(Menu menu)
{
	console->enableCustomFG();
	switch (menu)
	{
		case COLOR_PICKER: confConsoleTextColor(); break;
		default: choice = handleMenu(menu);
	}
	console->disableCustomFG();
	return choice;
}
void MenusCLI::confConsoleTextColor()
{
	if (ConsoleLib::ConsoleUtils::yesNo("Select color [Y/n]: "))
	{
		int max = ConsoleLib::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			console->enableCustomFG();
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
	short int red = ConsoleLib::ConsoleUtils::getIntSafe(0, 255);
	std::cout << "Green: ";
	short int green = ConsoleLib::ConsoleUtils::getIntSafe(0, 255);
	std::cout << "Blue: ";
	short int blue = ConsoleLib::ConsoleUtils::getIntSafe(0, 255);
	return ConsoleLib::Color{red, green, blue};
}
void MenusCLI::setConsole(ConsoleLib::IConsole* console2)
{
	this->console = console2;
}
MenusCLI::~MenusCLI()
{
}
} // Namespace ConsoleArt
