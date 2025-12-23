//==============================================================================
// File       : MenuTFD.h
// Author     : riyufuchi
// Created on : May 16, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_TINYFILEDIALOGS_MENUTFD_H_
#define CONSOLEART_TINYFILEDIALOGS_MENUTFD_H_

#include <functional>

#include "../../cli/MenuCLI.h"
#include "consolelib/tools/console_menu.h"

extern "C"
{
	#include "../../../include/tinyfiledialogs.h"
}

namespace consoleart
{

class MenuTFD : public MenuCLI
{
private:
	consolelib::ConsoleMenu mainMenu;
public:
	MenuTFD(consolelib::IConsole* console, std::function<void()> function);
	virtual ~MenuTFD() = default;
	virtual int mainMenuOptions() override;
	virtual consolelib::Color colorPicker() override;
	virtual void confConsoleTextColor() override;
};

} /* namespace consolelib */

#endif /* CONSOLEART_TINYFILEDIALOGS_MENUTFD_H_ */
