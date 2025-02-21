//==============================================================================
// File       : ControllerZenity.h
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : May 30, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_
#define CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_

#include "ControllerCLI.h"

namespace ConsoleArt
{
class ControllerZenity: public ControllerCLI
{
public:
	ControllerZenity(ConsoleLib::IConsole* console);
	virtual ~ControllerZenity();
	std::string inputImageName() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_ */
