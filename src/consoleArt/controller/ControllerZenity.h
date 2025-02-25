//==============================================================================
// File       : ControllerZenity.h
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : Feb 24, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_
#define CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_

#include "ControllerCLI.h"
#include "../cliZenity/MenuZenity.h"
#include "../cliZenity/NotifierZenity.h"

namespace ConsoleArt
{
class ControllerZenity: public ControllerCLI
{
public:
	ControllerZenity(ConsoleLib::IConsole* console);
	virtual ~ControllerZenity();
protected:
	virtual Images::Image* selectImage() override;
	virtual std::string inputImageName() override;
	virtual void showAboutApplicationInfo() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_ */
