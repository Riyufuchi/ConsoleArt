//==============================================================================
// File       : ProgressBarCLI.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ProgressBarCLI.h"

namespace ConsoleArt {

ProgressBarCLI::ProgressBarCLI(int maxStep) : AbstrProgressBar(maxStep)
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

} /* namespace ConsoleArt */
