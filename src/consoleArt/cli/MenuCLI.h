//============================================================================
// Name        : MenuCLI
// Author      : Riyufuchi
// Created on  : Mar 10, 2023
// Last Edit   : Dec 23, 2025
// Description : Methods for menus in CLI
//============================================================================
#ifndef _MenuUtils_HPP_
#define _MenuUtils_HPP_

#include <string>
#include <vector>
#include <map>

#include "consolelib/tools/color_tools.h"
#include "consolelib/tools/console_tools.h"
#include "consolelib/consoles/iconsole.hpp"

#include "../interfaces/IMenu.hpp"

namespace consoleart
{
class MenuCLI : public IMenu
{
private:
	int choice {0};
protected:
	std::map<Menu, std::vector<std::string>> menus;
	consolelib::IConsole* console;
public:
	MenuCLI(consolelib::IConsole* console);
	virtual ~MenuCLI();
	// Menus
	virtual int charSetMenu() override;
	virtual int printMenu() override;
	virtual consolelib::Color colorPicker() override;
	virtual int imageFilterOptions() override;
	virtual int imageEditOptions() override;
	virtual int mainMenuOptions() override;
	virtual int afterPrintOptions() override;
	virtual void confConsoleTextColor();
	// Setters
	void setConsole(consolelib::IConsole* console);
};
}
#endif
