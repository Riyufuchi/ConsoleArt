//==============================================================================
// File       : SelectImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : May 25, 2025
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

void SelectImageStateSDL::createUI()
{
	const int SIZE = 32;
	
	controller.iterateImagesAsync([&](Images::Image* image) {
		Images::Image* imgCopy = image;
		pane.addComponent(y, new sdl::StringButtonSDL(new sdl::StringSDL(image->getFilename(), FONT_BASE, SIZE, BASE_TEXT_COLOR, renderer), HOVER_TEXT_COLOR
		, [imgCopy, this]()
		{
			controller.setSelectedImage(imgCopy);
			stateManager.switchState(WindowState::MAIN);
		}));
		y++;
	});
	
}

void SelectImageStateSDL::handleTick(SDL_Event& event)
{
	pane.checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane.tickOnClick(); break;
		case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) stateManager.switchState(WindowState::MAIN); break;
	}
}

void SelectImageStateSDL::onWindowResize()
{
	pane.center(winInfo.w, winInfo.h);
	pane.reposeContent();
}

void SelectImageStateSDL::onReturn()
{
	y = 0;
	pane.clear();
	createUI();
	onWindowResize();
	//std::thread([&](){ controller.getMessenger().messageUser(AbstractNotifier::WARNING, "Not yet implemented."); }).detach();
	//stateManager.switchState(WindowState::MAIN);
}

void SelectImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
}

} /* namespace ConsoleArt */
