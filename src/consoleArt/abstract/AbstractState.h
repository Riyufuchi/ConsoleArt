//==============================================================================
// File       : AbstractState.h
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRACTSTATE_H_
#define CONSOLEART_ABSTRACT_ABSTRACTSTATE_H_

#include "AbstractNotifier.h"
#include "../controller/StateController.h"

namespace ConsoleArt
{
class AbstractState
{
protected:
	StateController& controller;
	AbstractNotifier* notifier;
public:
	AbstractState(StateController& controller, AbstractNotifier* notifier);
	virtual ~AbstractState();
};

} /* namespace ConsoleArt */
#endif /* CONSOLEART_ABSTRACT_ABSTRACTSTATE_H_ */
