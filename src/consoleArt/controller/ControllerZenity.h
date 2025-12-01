//==============================================================================
// File       : ControllerZenity.h
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_
#define CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_

#include <ConsoleMenu.h>

#include "ControllerCLI.h"
#include "../cli/zenity/MenuZenity.h"
#include "../cli/zenity/NotifierZenity.h"

namespace ConsoleArt
{
class ControllerZenity: public ControllerCLI
{
private:
	void printHeader();
protected:
	virtual std::string inputImageName() override;
	virtual IndexDataType selectImageMenu() override;
	virtual void showAboutApplicationInfo() override;
public:
	ControllerZenity(consolelib::IConsole* console);
	virtual ~ControllerZenity();
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_ */
