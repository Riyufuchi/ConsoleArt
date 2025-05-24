//==============================================================================
// File       : SelectImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : May 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AboutStateSDL.h"

namespace ConsoleArt
{
AboutStateSDL::AboutStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	this->y = 0;
	std::string string;
	for (auto line : std::views::split(GeneralTools::aboutApplication(), '\n'))
	{
		string = std::string(line.begin(), line.end());
		if (string.length() > 0)
		{
			pane.addComponent(y, new sdl::LabelSDL(string, FONT, SIZE, {255, 105, 180, 255}, renderer));
			y++;
		}
	}
}

AboutStateSDL::~AboutStateSDL()
{
}

void AboutStateSDL::handleTick(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		stateManager.switchState(WindowState::MAIN);
	}
}

void AboutStateSDL::onWindowResize()
{
	onReturn();
}

void AboutStateSDL::onReturn()
{
	pane.setX(std::max(8, (winInfo.w - pane.getWidth()) / 2));
	pane.setY(std::max(8, (winInfo.h - pane.getHeight()) / 2));
	pane.reposeContent();
}

void AboutStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
}

} /* namespace ConsoleArt */
