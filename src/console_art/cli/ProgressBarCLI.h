//==============================================================================
// File       : ProgressBarCLI.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_CLI_PROGRESSBARCLI_H_
#define CONSOLE_ART_CLI_PROGRESSBARCLI_H_

#include <iostream>

#include "../../console_art/abstract/AbstractProgressBar.h"

namespace consoleart
{
class ProgressBarCLI : AbstractProgressBar
{
public:
	ProgressBarCLI(int maxStep);
	~ProgressBarCLI();
	virtual void drawProgressBar() override;
};
} /* namespace consoleart */
#endif /* CONSOLE_ART_CLI_PROGRESSBARCLI_H_ */
