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
MainState::MainState(SDL_Renderer* renderer, WindowInfo& winInfo, std::function<void()> addImageFunc, std::function<void()> addImageAsyncFunc,
		std::function<bool(StringSDL*)> updateText) : StateSDL(renderer, winInfo), updateText(updateText)
{
	this->selectedImageString = new StringSDL("No image selected", "TF2Build.ttf", 24, {255, 105, 180, 255}, renderer);
	this->selectedImageString->setY(16);
	std::pair<int, int> square(32, 32);
	std::pair<int, int> rectangle(64, 32);
	std::pair<std::string, std::string> addImageBtn("1", "1H");
	std::pair<std::string, std::string> exitBtn("2", "2H");
	std::pair<std::string, std::string> configBtn("3", "3H");
	std::pair<std::string, std::string> selectBtn("4", "4H");
	std::pair<std::string, std::string> asyncBtn("5", "5H");
	std::pair<std::string, std::string> editBtn("6", "6H");
	std::pair<std::string, std::string> aboutBtn("7", "7H");
	this->sheet = new SpriteSheetSDL("ui.png", renderer);
	this->sheet->prepareTexturePair(addImageBtn, 0, 0, rectangle);
	this->sheet->prepareTexturePair(exitBtn, 0, 160, square);
	this->sheet->prepareTexturePair(configBtn, 0, 96, square);
	this->sheet->prepareTexturePair(selectBtn, 0, 32, rectangle);
	this->sheet->prepareTexturePair(asyncBtn, 128, 0, square);
	this->sheet->prepareTexturePair(editBtn, 128, 32, square);
	this->sheet->prepareTexturePair(aboutBtn, 128, 64, square);
	this->pane = new ContentPanelSDL(0, 0);
	// 0
	pane->addComponent(0, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexturePair(addImageBtn), addImageFunc));
	pane->addComponent(0, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(asyncBtn), addImageAsyncFunc));
	// 1
	pane->addComponent(1, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexturePair(selectBtn)));
	pane->addComponent(1, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(editBtn)));
	// 2
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(configBtn)));
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(aboutBtn), [&]() {  }));
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(exitBtn), [&]() { exitApplication(); }));
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
	this->font = selectedImageString->getFont();
	selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
}

MainState::~MainState()
{
	delete sheet;
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
	SDL_RenderClear(renderer);

	pane->draw(renderer);
	if (updateText(selectedImageString))
		selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
	selectedImageString->draw(renderer);
}

} /* namespace ConsoleArt */
