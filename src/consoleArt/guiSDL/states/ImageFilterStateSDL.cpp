//==============================================================================
// File       : ImageFilterStateSDL.cpp
// Author     : riyufuchi
// Created on : May 24, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageFilterStateSDL.h"

namespace ConsoleArt
{

ImageFilterStateSDL::ImageFilterStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager) : StateSDL(winInfo), AbstractState(controller, stateManager)
{
	pane.addComponent(0, new sdl::StringButtonSDL(new sdl::StringSDL("Back", FONT_BASE, 32, BASE_TEXT_COLOR, renderer), HOVER_TEXT_COLOR, [&]() { stateManager.switchState(WindowState::EDIT_IMAGE); }));
	onWindowResize();
}


void ImageFilterStateSDL::handleTick(SDL_Event& event)
{
	pane.checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane.tickOnClick(); break;
	}
}

void ImageFilterStateSDL::onWindowResize()
{
	pane.center(winInfo.w, winInfo.h);
	pane.reposeContent();
}

void ImageFilterStateSDL::onReturn()
{
}

void ImageFilterStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
}

} /* namespace ConsoleArt */
