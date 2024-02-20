//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : 20.02.2024
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include <string>

#include "../../inc/ConsoleUtility.h"
#include "../../inc/DefaultConsole.h"
#include "../interfaces/IMenu.hpp"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
private:
	int choice{0};
	ConsoleUtils::IConsole* console;
	void confConsoleTextColor();
public:
	enum Menu
	{
		CHAR_SET_SELECTION,
		PRINT_OPTIONS,
		MAIN_MENU,
		COLOR_PICKER
	};
	MenusCLI();
	MenusCLI(ConsoleUtils::IConsole* console);
	~MenusCLI();
	// Utils
	int invokeMenu(Menu menu);
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	ConsoleUtils::Color colorPicker() override;
	// Setters
	void setConsole(ConsoleUtils::IConsole* console);
};
}
#endif
