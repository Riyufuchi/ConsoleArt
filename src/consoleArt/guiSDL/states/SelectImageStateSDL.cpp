//==============================================================================
// File       : SelectImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "SelectImageStateSDL.h"

namespace ConsoleArt
{
SelectImageStateSDL::SelectImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	this->y = 0;
}

SelectImageStateSDL::~SelectImageStateSDL()
{
}

void SelectImageStateSDL::handleTick(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		stateManager.switchState(WindowState::MAIN);
	}
}

void SelectImageStateSDL::onWindowResize()
{
}

void SelectImageStateSDL::onReturn()
{
}

void SelectImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

} /* namespace ConsoleArt */
