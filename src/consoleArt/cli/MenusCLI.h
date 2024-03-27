//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : Mar 08, 2024
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include <string>

#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "DefaultConsole.h"
#include "../interfaces/IMenu.hpp"
#include "../../imageUtils/ImageToolsCLI.h"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
private:
	int choice{0};
	ConsoleLib::IConsole* console;
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
	MenusCLI(ConsoleLib::IConsole* console);
	~MenusCLI();
	// Utils
	int invokeMenu(Menu menu);
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	ConsoleLib::Color colorPicker() override;
	void displayImageInfo(Images::Image& image) override;
	// Setters
	void setConsole(ConsoleLib::IConsole* console);
};
}
#endif
