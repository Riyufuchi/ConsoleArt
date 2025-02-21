//==============================================================================
// File       : ProgressBarCLI.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLI_PROGRESSBARCLI_H_
#define CONSOLEART_CLI_PROGRESSBARCLI_H_

#include <iostream>

#include "../interfaces/AbstrProgressBar.h"

namespace ConsoleArt
{
class ProgressBarCLI : AbstrProgressBar
{
public:
	ProgressBarCLI(int maxStep);
	~ProgressBarCLI();
	virtual void drawProgressBar() override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CLI_PROGRESSBARCLI_H_ */
