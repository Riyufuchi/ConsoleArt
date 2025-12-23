//==============================================================================
// File       : AbstractState.h
// Author     : riyufuchi
// Created on : Mar 03, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_ABSTRACT_ABSTRACT_STATE_H_
#define CONSOLE_ART_ABSTRACT_ABSTRACT_STATE_H_

#include "../controller/controller.h"
#include "../gui/sdl/state_manager.h"

namespace consoleart
{
class AbstractState
{
protected:
	Controller& controller;
	StateManager& stateManager;
public:
	AbstractState(Controller& controller, StateManager& stateManager);
	virtual ~AbstractState();
};
} /* namespace consoleart */
#endif /* CONSOLE_ART_ABSTRACT_ABSTRACT_STATE_H_ */
