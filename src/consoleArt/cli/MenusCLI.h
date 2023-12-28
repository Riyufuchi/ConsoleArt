//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : 28.12.2023
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include <string>

#include "../../inc/ConsoleUtility.h"
#include "../interfaces/IMenu.hpp"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
private:
	int choice{0};
	ConsoleUtils::IConsole& console;
	void confConsoleTextColor();
public:
	enum Menu
	{
		CHAR_SET_SELECTION,
		PRINT_OPTIONS,
		MAIN_MENU,
		COLOR_PICKER
	};
	MenusCLI(ConsoleUtils::IConsole& console);
	~MenusCLI();
	// Utils
	int invokeMenu(Menu menu);
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	ConsoleUtils::Color colorPicker() override;
};
}
#endif
