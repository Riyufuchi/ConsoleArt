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

#include "../../inc/ColorUtils.h"
#include "../../inc/ConsoleUtils.h"
#include "../../inc/DefaultConsole.h"
#include "../interfaces/IMenu.hpp"
#include "../../imageUtils/ImageToolsCLI.h"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
private:
	int choice{0};
	ConsoleUtility::IConsole* console;
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
	MenusCLI(ConsoleUtility::IConsole* console);
	~MenusCLI();
	// Utils
	int invokeMenu(Menu menu);
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	ConsoleUtility::Color colorPicker() override;
	void displayImageInfo(Images::Image& image) override;
	// Setters
	void setConsole(ConsoleUtility::IConsole* console);
};
}
#endif
