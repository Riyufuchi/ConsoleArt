//==============================================================================
// File       : AbstractFilterState.h
// Author     : riyufuchi
// Created on : Mar 6, 2025
// Last edit  : Mar 6, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRACTFILTERSTATE_H_
#define CONSOLEART_ABSTRACT_ABSTRACTFILTERSTATE_H_

#include "AbstractState.h"

namespace ConsoleArt
{
class AbstractFilterState: public AbstractState
{
public:
	AbstractFilterState(Controller& controller, StateManager& stateManager);
	virtual ~AbstractFilterState();
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_ABSTRACT_ABSTRACTFILTERSTATE_H_ */
