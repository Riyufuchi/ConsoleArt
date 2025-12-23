//==============================================================================
// File       : ControllerTFD.h
// Author     : riyufuchi
// Created on : May 15, 2025
// Last edit  : Nov 09, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_CONTROLLER_CONTROLLERTFD_H_
#define CONSOLE_ART_CONTROLLER_CONTROLLERTFD_H_

#include "../../console_art/controller/ControllerCLI.h"
#include "../../console_art/gui/tinyFileDialogs/MenuTFD.h"
#include "../../console_art/gui/tinyFileDialogs/NotifierTFD.h"

namespace consoleart
{

class ControllerTFD : public ControllerCLI
{
public:
	ControllerTFD(consolelib::IConsole* console);
	virtual ~ControllerTFD() = default;
	void printHeader();
	virtual std::string inputImageName() override;
protected:
	virtual void showAboutApplicationInfo() override;
};

} /* namespace consolelib */

#endif /* CONSOLE_ART_CONTROLLER_CONTROLLERTFD_H_ */
