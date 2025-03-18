//==============================================================================
// File       : MenuZenity.h
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLIZENITY_MENUZENITY_H_
#define CONSOLEART_CLIZENITY_MENUZENITY_H_

#include <iostream>
#include <sstream>
#include <cstdlib> // For popen()
#include <functional>

#include "ConsoleMenu.h"

#include "ColorUtils.h"
#include "../tools/GeneralTools.hpp"
#include "../cli/MenuCLI.h"

namespace ConsoleArt
{

class MenuZenity: public MenuCLI
{
private:
	std::function<void()> function;
	//ConsoleLib::ConsoleMenu* mainMenu;
	int createZenityMenu(std::vector<std::string>& menu);
public:
	MenuZenity(ConsoleLib::IConsole* console, std::function<void()> function);
	~MenuZenity();
	virtual ConsoleLib::Color colorPicker() override;
	virtual int imageFilterOptions() override;
	virtual int charSetMenu() override;
	virtual int printMenu() override;
	virtual int imageEditOptions() override;
	virtual int mainMenuOptions() override;
protected:
	virtual void confConsoleTextColor() override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CLIZENITY_MENUZENITY_H_ */
