//==============================================================================
// File       : AbstractState.cpp
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AbstractState.h"

namespace ConsoleArt
{
AbstractState::AbstractState(StateController& controller, AbstractNotifier* notifier) : controller(controller), notifier(notifier)
{
}

AbstractState::~AbstractState()
{
}
} /* namespace ConsoleArt */
