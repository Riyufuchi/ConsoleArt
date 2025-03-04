//==============================================================================
// File       : StateManager.h
// Author     : riyufuchi
// Created on : Mar 2, 2025
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATEMANAGER_H_
#define CONSOLEART_GUISDL_STATEMANAGER_H_

#include <unordered_map>

#include "../../sdl/abstract/StateSDL.h"

namespace ConsoleArt
{
enum WindowState
{
	MAIN,
	EDIT_IMAGE,
	SHOW_IMAGE,
	SELECT_IMAGE,
	ABOUT,
	ASCII_CONVERTER
};
class StateManager
{
private:
	sdl::StateSDL*& currentState;
	std::unordered_map<WindowState, sdl::StateSDL*> windowStates;
public:
	StateManager(sdl::StateSDL*& currentState);
	virtual ~StateManager();
	void addNewState(WindowState windowState, sdl::StateSDL* newState);
	void switchState(WindowState windowState);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_STATEMANAGER_H_ */
