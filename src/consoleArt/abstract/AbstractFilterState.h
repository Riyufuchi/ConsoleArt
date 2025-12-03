//==============================================================================
// File       : AbstractFilterState.h
// Author     : riyufuchi
// Created on : Mar 6, 2025
// Last edit  : Mar 6, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRACTFILTERSTATE_H_
#define CONSOLEART_ABSTRACT_ABSTRACTFILTERSTATE_H_

#include "AbstractState.h"

namespace consoleart
{
class AbstractFilterState: public AbstractState
{
public:
	AbstractFilterState(Controller& controller, StateManager& stateManager);
	virtual ~AbstractFilterState();
};
} /* namespace consoleart */
#endif /* CONSOLEART_ABSTRACT_ABSTRACTFILTERSTATE_H_ */
