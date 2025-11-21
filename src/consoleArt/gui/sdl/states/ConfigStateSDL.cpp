//==============================================================================
// File       : ConfigStateSDL.cpp
// Author     : riyufuchi
// Created on : Nov 16, 2025
// Last edit  : Nov 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ConfigStateSDL.h"

namespace ConsoleArt
{
ConfigStateSDL::ConfigStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	this->y = 0;
	std::string text = "Image state controls:\nEscape -> returns to previous menu\nLeft arrow -> Moves multi-page images to left\n"
			"Right arrow -> Moves multi-page images to right\nSpace -> Stop/plays animated formats";
	std::string string;
	for (auto line : std::views::split(text, '\n'))
	{
		string = std::string(line.begin(), line.end());
		if (string.length() > 0)
		{
			pane.addComponent(y, new sdl::LabelSDL(string, FONT_PROF, SIZE, BASE_TEXT_COLOR, renderer));
			y++;
		}
	}
}

ConfigStateSDL::~ConfigStateSDL()
{
}

void ConfigStateSDL::handleTick(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		stateManager.switchState(WindowState::MAIN);
	}
}

void ConfigStateSDL::onWindowResize()
{
	onReturn();
}

void ConfigStateSDL::onReturn()
{
	pane.setX(std::max(8, (winInfo.w - pane.getWidth()) / 2));
	pane.setY(std::max(8, (winInfo.h - pane.getHeight()) / 2));
	pane.reposeContent();
}

void ConfigStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
}

} /* namespace ConsoleArt */
