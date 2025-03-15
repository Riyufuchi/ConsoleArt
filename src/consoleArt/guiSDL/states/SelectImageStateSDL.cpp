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
	pane = new sdl::ContentPanelSDL(0, 0);
}

SelectImageStateSDL::~SelectImageStateSDL()
{
	delete pane;
}

void SelectImageStateSDL::createUI()
{
	const std::string FONT = "assets/TF2Build.ttf";
	const int SIZE = 32;
	const SDL_Color color {255, 105, 180, 255};
	const SDL_Color colorHover {255, 179, 222, 255};
	
	
	controller.iterateImagesAsync([&](Images::Image* image) {
		Images::Image* imgCopy = image;
		pane->addComponent(y, new sdl::StringButtonSDL(0, 0,
		new sdl::StringSDL(image->getFilename(), FONT, SIZE, color, renderer), colorHover
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
	pane->checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane->tickOnClick(); break;
		case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) stateManager.switchState(WindowState::MAIN); break;
	}
}

void SelectImageStateSDL::onWindowResize()
{
	pane->center(winInfo.w, winInfo.h);
	pane->reposeContent();
}

void SelectImageStateSDL::onReturn()
{
	y = 0;
	pane->clear();
	createUI();
	onWindowResize();
	//std::thread([&](){ controller.getMessenger().messageUser(AbstractNotifier::WARNING, "Not yet implemented."); }).detach();
	//stateManager.switchState(WindowState::MAIN);
}

void SelectImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane->draw(renderer);
}

} /* namespace ConsoleArt */
