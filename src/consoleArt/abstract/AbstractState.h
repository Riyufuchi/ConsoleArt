//==============================================================================
// File       : AbstractState.h
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRACTSTATE_H_
#define CONSOLEART_ABSTRACT_ABSTRACTSTATE_H_

#include "../controller/Controller.h"
#include "../guiSDL/StateManager.h"

namespace ConsoleArt
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
} /* namespace ConsoleArt */
#endif /* CONSOLEART_ABSTRACT_ABSTRACTSTATE_H_ */
