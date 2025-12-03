//==============================================================================
// File       : ControllerTFD.h
// Author     : riyufuchi
// Created on : May 15, 2025
// Last edit  : Nov 09, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_CONTROLLERTFD_H_
#define CONSOLEART_CONTROLLER_CONTROLLERTFD_H_

#include "ControllerCLI.h"
#include "../gui/tinyFileDialogs/NotifierTFD.h"
#include "../gui/tinyFileDialogs/MenuTFD.h"

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

#endif /* CONSOLEART_CONTROLLER_CONTROLLERTFD_H_ */
