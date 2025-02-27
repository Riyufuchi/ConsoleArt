//==============================================================================
// File       : AbstrctState.h
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRCTSTATE_H_
#define CONSOLEART_ABSTRACT_ABSTRCTSTATE_H_

#include "../controller/StateController.h"

namespace ConsoleArt
{
class AbstrctState
{
protected:
	StateController& controller;
public:
	AbstrctState(StateController& controller);
	virtual ~AbstrctState();
	virtual void render() = 0;
};

} /* namespace ConsoleArt */
#endif /* CONSOLEART_ABSTRACT_ABSTRCTSTATE_H_ */
