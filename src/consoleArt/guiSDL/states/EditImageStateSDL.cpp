//==============================================================================
// File       : EditImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "EditImageStateSDL.h"

namespace ConsoleArt {

EditImageStateSDL::EditImageStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, StateManager& stateManager) : StateSDL(winInfo), buttons(buttons), controller(controller), stateManager(stateManager)
{
	this->pane = new sdl::ContentPanelSDL(0, 0);
	this->pane->addComponent(0, new sdl::ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::CONVER_TO_ASCII, false)));
	this->pane->addComponent(0, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::SHOW_IMAGE, true), [&]() { stateManager.switchState(WindowState::SHOW_IMAGE); }));
	this->pane->addComponent(1, new sdl::ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::IMAGE_FILTER, false)));
	this->pane->addComponent(1, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::IMAGE_INFO, true), [&]()
	{
		if (controller.getSelectedImage())
			controller.getMessenger().displayImageInfo(*controller.getSelectedImage());
	}));
	this->pane->addComponent(2, new sdl::ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::WATERMARK, false)));
	this->pane->addComponent(2, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::BACK, true), [&]() { stateManager.switchState(WindowState::MAIN); }));
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

EditImageStateSDL::~EditImageStateSDL()
{
	delete pane;
}

void EditImageStateSDL::handleTick(SDL_Event& event)
{
	pane->checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane->tickOnClick();break;
	}
}

void EditImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
	pane->draw(renderer);
}

void EditImageStateSDL::onReturn()
{
	pane->setX((winInfo.w/ 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

void EditImageStateSDL::onWindowResize()
{
	SDL_RenderSetLogicalSize(renderer, winInfo.w, winInfo.h);
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

} /* namespace ConsoleArt */
