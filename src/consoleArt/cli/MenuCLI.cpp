//============================================================================
// Name        : MenuCLI
// Author      : Riyufuchi
// Created on  : Dec 28,2023
// Last Edit   : Nov 07, 2025
//============================================================================
#include "MenuCLI.h"

namespace consoleart
{
MenuCLI::MenuCLI(consolelib::IConsole* console) : console(console)
{
	menus[Menu::MAIN_MENU] = { "Load image", "Load all images", "Select image", "Image actions", "List images", "Settings", "About", "Exit"};
	menus[Menu::CHAR_SET_SELECTION] = { "BASIC - █#@%=+:-. ", "PRECISE", "DETAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█",
			"BASIC_INVERTED", "PRECISE_INVERTED", "SHADES", "SHADES_INVERTED", "Exit" };
	menus[Menu::PRINT_OPTIONS] = { "Classic", "Classic colored", "Pixel colored", "To text file", "Exit"};
	menus[Menu::AFTER_PRINT_OPTIONS] = { "Reconvert", "Reprint", "Back to main menu"};
	menus[Menu::IMAGE_ACTION_OPTIONS] = {"Convert to ASCII", "Add signature", "Apply filter"};
	menus[Menu::FILTERS] = {"Matrix", "Purplefier", "Purplefier soft", "Purplefier shading", "Purplefier shading soft"};
}
MenuCLI::~MenuCLI()
{
}
int MenuCLI::mainMenuOptions()
{
	return consolelib::ConsoleUtils::basicMenu(menus.at(Menu::MAIN_MENU), *console);
}
void MenuCLI::confConsoleTextColor()
{
	if (consolelib::ConsoleUtils::yesNo("Select color [Y/n]: "))
	{
		int max = consolelib::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			console->enableCustomFG();
			std::cout << i + 1 << ". ";
			console->out(consolelib::ColorUtils::getColor(static_cast<consolelib::ColorPallete>(i)), consolelib::ColorUtils::colorPaletteNames[i]);
			std::cout << "\n";
		}
		console->setDefaultTextColor(consolelib::ColorUtils::getColor(static_cast<consolelib::ColorPallete>(consolelib::ConsoleUtils::getIntSafe(1, max) - 1)));
	}
	else if(consolelib::ConsoleUtils::yesNo("Custom color [Y/n]: "))
	{
		console->setDefaultTextColor(MenuCLI::colorPicker());
	}
}
// Menus
int MenuCLI::charSetMenu()
{
	return consolelib::ConsoleUtils::basicMenu(menus.at(Menu::CHAR_SET_SELECTION), *console);
}
int MenuCLI::printMenu()
{
	return consolelib::ConsoleUtils::basicMenu(menus.at(Menu::PRINT_OPTIONS), *console);
}
consolelib::Color MenuCLI::colorPicker()
{
	std::cout << "Red: ";
	short int red = consolelib::ConsoleUtils::getIntSafe(0, 255);
	std::cout << "Green: ";
	short int green = consolelib::ConsoleUtils::getIntSafe(0, 255);
	std::cout << "Blue: ";
	short int blue = consolelib::ConsoleUtils::getIntSafe(0, 255);
	return consolelib::Color{red, green, blue};
}
void MenuCLI::setConsole(consolelib::IConsole* console2)
{
	this->console = console2;
}

int MenuCLI::imageEditOptions()
{
	return consolelib::ConsoleUtils::basicMenu(menus.at(Menu::IMAGE_ACTION_OPTIONS), *console);
}

int MenuCLI::imageFilterOptions()
{
	return consolelib::ConsoleUtils::basicMenu(menus.at(Menu::FILTERS), *console);
}

int MenuCLI::afterPrintOptions()
{
	return consolelib::ConsoleUtils::basicMenu(menus.at(Menu::AFTER_PRINT_OPTIONS), *console);
}

} // Namespace consoleart
