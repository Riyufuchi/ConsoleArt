//==============================================================================
// File       : AbstractState.cpp
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AbstractState.h"

namespace ConsoleArt {

AbstractState::AbstractState(Controller& controller, StateManager& stateManager) : controller(controller), stateManager(stateManager)
{
}

AbstractState::~AbstractState()
{
}
} /* namespace ConsoleArt */
