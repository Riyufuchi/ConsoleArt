//==============================================================================
// File       : ControllerTFD.h
// Author     : riyufuchi
// Created on : May 15, 2025
// Last edit  : Nov 09, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_CONTROLLERTFD_H_
#define CONSOLEART_CONTROLLER_CONTROLLERTFD_H_

#include "ControllerCLI.h"
#include "../tinyFileDialogs/NotifierTFD.h"
#include "../tinyFileDialogs/MenuTFD.h"

namespace ConsoleArt
{

class ControllerTFD : public ControllerCLI
{
public:
	ControllerTFD(ConsoleLib::IConsole* console);
	virtual ~ControllerTFD() = default;
	void printHeader();
	virtual std::string inputImageName() override;
protected:
	virtual void showAboutApplicationInfo() override;
};

} /* namespace ConsoleLib */

#endif /* CONSOLEART_CONTROLLER_CONTROLLERTFD_H_ */
