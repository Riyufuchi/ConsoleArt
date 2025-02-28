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

EditImageState::EditImageState(SDL_Renderer* renderer, WindowInfo& winInfo, std::function<void()> baclBtnEvt) : StateSDL(renderer, winInfo)
{
	this->text = new StringSDL("Test state 2", "TF2Build.ttf", 24, {255, 105, 180, 255}, renderer);
	this->text->repose(16, 16);
	this->buttons = new ButtonBuilder(renderer);
	this->pane = new ContentPanelSDL(0, 0);
	this->pane->addComponent(0, new ImageButtonSDL(0,0,100,100, buttons->getButtonTextureFor(ButtonType::BACK), baclBtnEvt));
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

EditImageState::~EditImageState()
{
	delete text;
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
	text->draw();
	pane->draw(renderer);
}

void EditImageState::onReturn()
{
	pane->setX((winInfo.w/ 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
}

} /* namespace ConsoleArt */
