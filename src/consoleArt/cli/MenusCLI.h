//============================================================================
// Name        : MenusCLI
// Author      : Riyufuchi
// Created on  : 10.03.2023
// Last Edit   : Feb 24, 2025
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include <string>
#include <vector>
#include <map>

#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "DefaultConsole.h"

#include "../interfaces/IMenu.hpp"

namespace ConsoleArt
{
class MenusCLI : public IMenu
{
public:
private:
	int choice {0};
protected:
	std::map<Menu, std::vector<const char*>> menus;
	ConsoleLib::IConsole* console;
	virtual void confConsoleTextColor();
public:
	MenusCLI();
	MenusCLI(ConsoleLib::IConsole* console);
	virtual ~MenusCLI();
	// Utils
	void printMainMenu();
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	[[deprecated("For backwards compatibility only")]]
	int invokeMenu(Menu id) override;
	virtual ConsoleLib::Color colorPicker() override;
	// Setters
	void setConsole(ConsoleLib::IConsole* console);
};
}
#endif
