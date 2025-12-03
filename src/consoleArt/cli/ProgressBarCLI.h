//==============================================================================
// File       : ProgressBarCLI.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CLI_PROGRESSBARCLI_H_
#define CONSOLEART_CLI_PROGRESSBARCLI_H_

#include <iostream>

#include "../abstract/AbstractProgressBar.h"

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
#endif /* CONSOLEART_CLI_PROGRESSBARCLI_H_ */
