//==============================================================================
// File       : ControllerGuiZen.h
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : May 30, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_
#define CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_

#include "../../controller/ControllerCLI.h"

namespace ConsoleArt
{
class ControllerGuiZen: public ControllerCLI
{
public:
	ControllerGuiZen(ConsoleLib::IConsole* console);
	virtual ~ControllerGuiZen();
	std::string inputImageName() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUI_ZENITY_CONTROLLERGUIZEN_H_ */
