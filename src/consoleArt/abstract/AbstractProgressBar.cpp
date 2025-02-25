//==============================================================================
// File       : AbstrProgressBar.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AbstractProgressBar.h"

namespace ConsoleArt
{
AbstractProgressBar::AbstractProgressBar(int maxStep) : maxStep(maxStep), currentStep(-1)
{
}

AbstractProgressBar::~AbstractProgressBar()
{
}
} /* namespace ConsoleArt */
