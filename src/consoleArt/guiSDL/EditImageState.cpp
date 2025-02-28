//==============================================================================
// File       : EditImageState.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "EditImageState.h"

namespace ConsoleArt {

EditImageState::EditImageState(SDL_Renderer* renderer, WindowInfo& winInfo, ButtonBuilder& buttons, std::function<void()> baclBtnEvt) : StateSDL(renderer, winInfo), buttons(buttons)
{
	this->pane = new ContentPanelSDL(0, 0);
	this->pane->addComponent(0, new ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::CONVER_TO_ASCII, false), baclBtnEvt));
	this->pane->addComponent(1, new ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::IMAGE_FILTER, false), baclBtnEvt));
	this->pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::BACK, true), baclBtnEvt));
	this->pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::BACK, true), baclBtnEvt));
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

EditImageState::~EditImageState()
{
	delete pane;
}

void EditImageState::handleTick(SDL_Event& event)
{
	pane->checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane->tickOnClick();break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				// (Optional) Adjust renderer size if needed
				SDL_RenderSetLogicalSize(renderer, event.window.data1, event.window.data2);
				pane->setX((event.window.data1 / 2) - pane->getWidth() / 2);
				pane->setY((event.window.data2 / 2) - pane->getHeight() / 2);
				pane->reposeContent();
			}
		break;
	}
}

void EditImageState::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
	pane->draw(renderer);
}

void EditImageState::onReturn()
{
	pane->setX((winInfo.w/ 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

} /* namespace ConsoleArt */
