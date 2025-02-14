//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : Feb 13, 2025
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include <string>
#include <vector>

#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "DefaultConsole.h"

#include "../interfaces/IMenu.hpp"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
private:
	int choice{0};
	ConsoleLib::IConsole* console;
	void confConsoleTextColor();
protected:
	std::vector<std::vector<const char*>> menus;
public:
	enum Menu
	{
		MAIN_MENU,
		CHAR_SET_SELECTION,
		PRINT_OPTIONS,
		// Dynamic menus
		COLOR_PICKER,
		MENU_COUNT
	};
	MenusCLI();
	MenusCLI(ConsoleLib::IConsole* console);
	~MenusCLI();
	// Utils
	void printMainMenu();
	int invokeMenu(Menu menu);
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	int handleMenu(int id) override;
	ConsoleLib::Color colorPicker() override;
	// Setters
	void setConsole(ConsoleLib::IConsole* console);
};
}
#endif
