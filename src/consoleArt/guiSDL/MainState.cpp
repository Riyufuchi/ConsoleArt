//==============================================================================
// File       : MainState.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MainState.h"

namespace ConsoleArt
{
MainState::MainState(SDL_Renderer* renderer, WindowInfo& winInfo, ButtonBuilder& buttons, std::function<void()> addImageFunc, std::function<void()> addImageAsyncFunc,
		std::function<bool(StringSDL*)> updateText, std::function<void()> switchState) : StateSDL(renderer, winInfo), buttons(buttons), updateText(updateText)
{
	this->selectedImageString = new StringSDL("No image selected", "TF2Build.ttf", 24, {255, 105, 180, 255}, renderer);
	this->selectedImageString->setY(16);
	this->pane = new ContentPanelSDL(0, 0);
	// 0
	pane->addComponent(0, new ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::LOAD, false), addImageFunc));
	pane->addComponent(0, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::LOAD_ALL, true), addImageAsyncFunc));
	// 1
	pane->addComponent(1, new ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::SELECT_IMAGE, false)));
	pane->addComponent(1, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::EDIT_IMAGE, true), switchState));
	// 2
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::SETTINGS, true)));
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::ABOUT, true), [&]() {  }));
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::EXIT, true), [&]() { exitApplication(); }));
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
	this->font = selectedImageString->getFont();
	selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
}

MainState::~MainState()
{
	delete pane;
	delete selectedImageString;
}

void MainState::handleTick(SDL_Event &event)
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
				selectedImageString->repose((event.window.data1 / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
			}
		break;
	}
}

void MainState::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
	pane->draw(renderer);
	if (updateText(selectedImageString))
		selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
	selectedImageString->draw(renderer);
}

void MainState::onReturn()
{
	pane->setX((winInfo.w/ 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
	selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
}

} /* namespace ConsoleArt */
