//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 28.12.2023
// Last Edit   : Mar 03, 2024
//============================================================================
#include "MenusCLI.h"

namespace ConsoleArt
{
MenusCLI::MenusCLI(ConsoleUtils::IConsole* console) : console(console)
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
	if (ConsoleUtils::ConsoleUtility::yesNo("Select color [Y/n]: "))
	{
		int max = ConsoleUtils::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			console->defaultTextColor();
			std::cout << i + 1 << ". ";
			console->out(ConsoleUtils::ColorUtils::getColor(static_cast<ConsoleUtils::ColorPallete>(i)), ConsoleUtils::ColorUtils::colorPaletteNames[i]);
			std::cout << "\n";
		}
		console->setDefaultTextColor(ConsoleUtils::ColorUtils::getColor(static_cast<ConsoleUtils::ColorPallete>(ConsoleUtils::ConsoleUtility::getIntSafe(1, max) - 1)));
	}
	else if(ConsoleUtils::ConsoleUtility::yesNo("Custom color [Y/n]: "))
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
	return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}
int MenusCLI::actionMenu()
{
	const char* menuItems[] = { "Load image", "Load all images", "Select image", "List images", "Configure console color", "Exit application"};
	return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}
int MenusCLI::printMenu()
{
	const char* menuItems[] = { "Classic", "Classic colored", "Pixel colored", "To text file", "Back to main menu"};
	return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}
ConsoleUtils::Color MenusCLI::colorPicker()
{
	std::cout << "Red: ";
	int red = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
	std::cout << "Green: ";
	int green = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
	std::cout << "Blue: ";
	int blue = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
	return ConsoleUtils::ColorUtils::newColor(red, green, blue);
}
void MenusCLI::setConsole(ConsoleUtils::IConsole* console2)
{
	this->console = console2;
}
MenusCLI::~MenusCLI()
{
}
} // Namespace ConsoleArt
