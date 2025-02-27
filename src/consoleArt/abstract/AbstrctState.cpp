//==============================================================================
// File       : AbstrctState.cpp
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AbstrctState.h"

namespace ConsoleArt {

AbstrctState::AbstrctState(StateController& controller) : controller(controller)
{
}

AbstrctState::~AbstrctState()
{
}
} /* namespace ConsoleArt */
