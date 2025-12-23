//==============================================================================
// File       : StateManager.cpp
// Author     : riyufuchi
// Created on : Mar 02, 2025
// Last edit  : Dec 03, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../../console_art/gui/sdl/StateManager.h"

namespace consoleart {

StateManager::StateManager(sdl::StateSDL*& currentState) : currentState(currentState)
{
}

StateManager::~StateManager()
{
	for (auto& pair : windowStates)
	{
		delete pair.second;
		pair.second = nullptr;
	}
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
} /* namespace consoleart */
