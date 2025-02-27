//==============================================================================
// File       : StateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Feb 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "StateSDL.h"

namespace ConsoleArt
{
StateSDL::StateSDL(SDL_Renderer* renderer, StateController& controller, WindowInfo& winInfo) : AbstrctState(controller), renderer(renderer), winInfo(winInfo)
{
}

StateSDL::~StateSDL()
{
}
void StateSDL::exitApplication()
{

}
} /* namespace ConsoleArt */
