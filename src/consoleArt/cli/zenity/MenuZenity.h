//==============================================================================
// File       : MenuZenity.h
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CLIZENITY_MENUZENITY_H_
#define CONSOLEART_CLIZENITY_MENUZENITY_H_

#include <iostream>
#include <sstream>
#include <cstdlib> // For popen()
#include <functional>

#include "ConsoleMenu.h"

#include "ColorUtils.h"
#include "../../tools/GeneralTools.hpp"
#include "../MenuCLI.h"

namespace consoleart
{

class MenuZenity: public MenuCLI
{
private:
	consolelib::ConsoleMenu mainMenu;
	consolelib::ConsoleMenu editImageOptionsMenu;
	int createZenityMenu(std::vector<std::string>& menu);
public:
	MenuZenity(consolelib::IConsole* console, std::function<void()> function);
	~MenuZenity();
	virtual consolelib::Color colorPicker() override;
	virtual int imageFilterOptions() override;
	virtual int charSetMenu() override;
	virtual int printMenu() override;
	virtual int imageEditOptions() override;
	virtual int mainMenuOptions() override;
protected:
	virtual void confConsoleTextColor() override;
};

} /* namespace consoleart */

#endif /* CONSOLEART_CLIZENITY_MENUZENITY_H_ */
