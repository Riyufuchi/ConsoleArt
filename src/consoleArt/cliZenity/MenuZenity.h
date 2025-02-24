//==============================================================================
// File       : MenuZenity.h
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Feb 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLIZENITY_MENUZENITY_H_
#define CONSOLEART_CLIZENITY_MENUZENITY_H_

#include <iostream>
#include <sstream>
#include <cstdlib> // For popen()

#include "../cli/MenusCLI.h"
#include "ColorUtils.h"

namespace ConsoleArt
{

class MenuZenity: public MenusCLI
{
public:
	MenuZenity(ConsoleLib::IConsole* console);
	~MenuZenity();
	virtual ConsoleLib::Color colorPicker() override;
protected:
	virtual void confConsoleTextColor() override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CLIZENITY_MENUZENITY_H_ */
