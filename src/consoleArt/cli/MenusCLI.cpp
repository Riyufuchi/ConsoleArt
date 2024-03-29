//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 28.12.2023
// Last Edit   : Mar 08, 2024
//============================================================================
#include "MenusCLI.h"

namespace ConsoleArt
{
MenusCLI::MenusCLI(ConsoleLib::IConsole* console) : console(console)
{
}
int MenusCLI::invokeMenu(Menu menu)
{
	console->defaultTextColor();
	switch (menu)
	{
		case CHAR_SET_SELECTION: choice = charSetMenu(); break;
		case PRINT_OPTIONS: choice = printMenu(); break;
		case MAIN_MENU: choice = actionMenu(); break;
		case COLOR_PICKER: confConsoleTextColor(); break;
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
	const char* menuItems[] = { "BASIC - █#@%=+:-. ", "PRECISE", "DEATAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█", "BASIC_INVERTED", "PRECISE_INVERTED", "SHADES", "SHADES_INVERTED", "Back" };
	return ConsoleLib::ConsoleUtils::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}
int MenusCLI::actionMenu()
{
	const char* menuItems[] = { "Load image", "Load all images", "Select image", "List images", "Configure console color", "Exit application"};
	return ConsoleLib::ConsoleUtils::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}
int MenusCLI::printMenu()
{
	const char* menuItems[] = { "Classic", "Classic colored", "Pixel colored", "To text file", "Back to main menu"};
	return ConsoleLib::ConsoleUtils::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
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
