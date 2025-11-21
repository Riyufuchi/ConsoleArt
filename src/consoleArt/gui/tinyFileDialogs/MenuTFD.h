//==============================================================================
// File       : MenuTFD.h
// Author     : riyufuchi
// Created on : May 16, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_TINYFILEDIALOGS_MENUTFD_H_
#define CONSOLEART_TINYFILEDIALOGS_MENUTFD_H_

#include <functional>

#include "../../cli/MenuCLI.h"
#include "ConsoleMenu.h"

extern "C"
{
	#include "../../../include/tinyfiledialogs.h"
}

namespace ConsoleArt
{

class MenuTFD : public MenuCLI
{
private:
	ConsoleLib::ConsoleMenu mainMenu;
public:
	MenuTFD(ConsoleLib::IConsole* console, std::function<void()> function);
	virtual ~MenuTFD() = default;
	virtual int mainMenuOptions() override;
	virtual ConsoleLib::Color colorPicker() override;
	virtual void confConsoleTextColor() override;
};

} /* namespace ConsoleLib */

#endif /* CONSOLEART_TINYFILEDIALOGS_MENUTFD_H_ */
