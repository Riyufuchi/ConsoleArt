//==============================================================================
// File       : AbstractFilterState.cpp
// Author     : riyufuchi
// Created on : Mar 6, 2025
// Last edit  : Mar 6, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/abstract/AbstractFilterState.h"

namespace consoleart {

AbstractFilterState::AbstractFilterState(Controller& controller, StateManager& stateManager) : AbstractState(controller, stateManager)
{
}

AbstractFilterState::~AbstractFilterState()
{
}

} /* namespace consoleart */
