//============================================================================
// Name        : MenuUtility
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : 27.12.2023
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include "../../inc/ConsoleUtility.h"
#include "../interfaces/IMenu.hpp"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
private:
	int choice{0};
	ConsoleUtils::IConsole& console;
public:
	enum Menu
	{
		CHAR_SET_SELECTION,
		PRINT_OPTIONS,
		MAIN_MENU
	};
	MenusCLI(ConsoleUtils::IConsole& console) : console(console)
	{
	}

	int invokeMenu(Menu menu)
	{
		console.defaultTextColor();
		switch (menu)
		{
			case CHAR_SET_SELECTION: choice = charSetMenu(); break;
			case PRINT_OPTIONS: choice = printMenu(); break;
			case MAIN_MENU: choice = actionMenu(); break;
		}
		console.resetTextColor();
		return choice;
	}

	int charSetMenu() override
	{
		const char* menuItems[] = { "BASIC - █#@%=+:-. ", "PRECISE", "DEATAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█", "BASIC_INVERTED", "PRECISE_INVERTED", "Back" };
		return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
	}
	int actionMenu() override
	{
		const char* menuItems[] = { "Load image", "Load all images", "Select image", "List images", "Configure console color", "Exit application"};
		return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
	}
	int printMenu() override
	{
		const char* menuItems[] = { "Classic", "Classic colored", "Pixel colored", "To text file", "Back to main menu"};
		return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
	}
	~MenusCLI()
	{
	}
};
}
#endif
