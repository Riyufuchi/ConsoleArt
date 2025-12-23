//==============================================================================
// File       : StateManager.h
// Author     : riyufuchi
// Created on : Mar 02, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATEMANAGER_H_
#define CONSOLEART_GUISDL_STATEMANAGER_H_

#include <unordered_map>

#include "component_sdl_lib/base/state_sdl.h"

namespace consoleart
{
enum WindowState
{
	MAIN,
	EDIT_IMAGE,
	SHOW_IMAGE,
	SELECT_IMAGE,
	ABOUT,
	ASCII_CONVERTER,
	WATERMARK,
	FILTER_IMAGE,
	CONFIG
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
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_STATEMANAGER_H_ */
