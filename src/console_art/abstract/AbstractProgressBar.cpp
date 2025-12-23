//==============================================================================
// File       : AbstrProgressBar.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/abstract/AbstractProgressBar.h"

namespace consoleart
{
AbstractProgressBar::AbstractProgressBar(int maxStep) : maxStep(maxStep), currentStep(-1)
{
}

AbstractProgressBar::~AbstractProgressBar()
{
}
} /* namespace consoleart */
