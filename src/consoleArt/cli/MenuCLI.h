//============================================================================
// Name        : MenuCLI
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
class MenuCLI : public IMenu
{
public:
private:
	int choice {0};
protected:
	std::map<Menu, std::vector<std::string>> menus;
	ConsoleLib::IConsole* console;
public:
	MenuCLI();
	MenuCLI(ConsoleLib::IConsole* console);
	virtual ~MenuCLI();
	// Utils
	int printMainMenu();
	// Menus
	int charSetMenu() override;
	int actionMenu() override;
	int printMenu() override;
	virtual ConsoleLib::Color colorPicker() override;
	virtual int imageFilterOptions() override;
	virtual int imageEditOptions() override;
	virtual void confConsoleTextColor();
	// Setters
	void setConsole(ConsoleLib::IConsole* console);
};
}
#endif
