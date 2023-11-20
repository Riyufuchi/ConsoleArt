//============================================================================
// Name        : MenuUtility
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : 13.10.2023
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include "../inc/ConsoleUtility.h"

namespace ConsoleArt
{
class MenuUtils
{
private:
public:
	MenuUtils()
	{
	}

	static int charSetMenu()
	{
		const char* menuItems[] = { "BASIC - █#@%=+:-. ", "PRECISE", "DEATAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█", "BASIC_INVERTED", "PRECISE_INVERTED" };
		return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
	}

	static int actionMenu()
	{
		const char* menuItems[] = { "Load image", "Select image", "Configure console color", "Exit application"};
		return ConsoleUtils::ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
	}

	~MenuUtils()
	{
	}
};
}

#endif