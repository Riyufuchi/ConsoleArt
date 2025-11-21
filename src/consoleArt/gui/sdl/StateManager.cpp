//==============================================================================
// File       : StateManager.cpp
// Author     : riyufuchi
// Created on : Mar 2, 2025
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "StateManager.h"

namespace ConsoleArt {

StateManager::StateManager(sdl::StateSDL*& currentState) : currentState(currentState)
{
}

StateManager::~StateManager()
{
	for (auto& pair : windowStates)
		delete pair.second;
}
void StateManager::addNewState(WindowState windowState, sdl::StateSDL* newState)
{
	if (newState)
		windowStates[windowState] = newState;
}
void StateManager::switchState(WindowState windowState)
{
	auto it = windowStates.find(windowState);
	if (it != windowStates.end())
	{
		currentState = it->second;
		currentState->onReturn();
	}
}
} /* namespace ConsoleArt */
