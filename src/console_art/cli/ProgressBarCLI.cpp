//==============================================================================
// File       : ProgressBarCLI.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/cli/ProgressBarCLI.h"

namespace consoleart
{
ProgressBarCLI::ProgressBarCLI(int maxStep) : AbstractProgressBar(maxStep)
{
}

ProgressBarCLI::~ProgressBarCLI()
{
}

void ProgressBarCLI::drawProgressBar()
{
	currentStep++;
	std::cout << "\r" << "[" << currentStep << " / " << maxStep << "]";
}
} /* namespace consoleart */
