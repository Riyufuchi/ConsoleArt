//==============================================================================
// File       : WatermarkStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 8, 2025
// Last edit  : Mar 8, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "WatermarkStateSDL.h"

namespace ConsoleArt
{
WatermarkStateSDL::WatermarkStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	const std::string FONT = "assets/TF2secondary.ttf";
	const int SIZE = 32;
	const SDL_Color COLOR {255, 105, 180, 255};
	this->watermark = nullptr;
	this->textUpdated = false;
	this->selectedWatermark = new sdl::LabelSDL("No watermark selected", FONT, SIZE, COLOR, renderer);
	this->selectedWatermark->setY(16);
	this->pane = new sdl::ContentPanelSDL(0, 0);
	this->pane->addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::SELECT, true), [&]() { std::thread([&](){ selectWatermarkEvent(); }).detach(); }));
	this->pane->addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::APPLY, true), [&]() { std::thread([&](){ applytWatermarkEvent(); }).detach(); }));
	this->pane->addComponent(1, new sdl::ImageButtonSDL(256, 128, buttons.getButtonTextureFor(ButtonType::BACK, false), [&]() { stateManager.switchState(WindowState::EDIT_IMAGE); }));

	onWindowResize();
}

WatermarkStateSDL::~WatermarkStateSDL()
{
	delete pane;
	delete selectedWatermark;
}

void WatermarkStateSDL::handleTick(SDL_Event& event)
{
	pane->checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			pane->tickOnClick();
		break;
		case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) stateManager.switchState(WindowState::EDIT_IMAGE); break;
	}
}

void WatermarkStateSDL::onWindowResize()
{
	pane->center(winInfo.w, winInfo.h);
	pane->reposeContent();
	selectedWatermark->center(winInfo.w, pane->getY());
}

void WatermarkStateSDL::onReturn()
{
	onWindowResize();
}

void WatermarkStateSDL::selectWatermarkEvent()
{
	watermark = controller.loadImageAsync(controller.inputImageName());
	if (watermark && watermark->isLoaded())
	{
		textUpdated = true;
	}
}

void WatermarkStateSDL::applytWatermarkEvent()
{
	if (watermark && ImageUtils::ImageTools::signatureToImage(*controller.getSelectedImage(), *watermark))
		controller.getMessenger().messageUser("Watermark successfully applied to the image.");
}

void WatermarkStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane->draw(renderer);
	if (textUpdated)
	{
		textUpdated = false;
		selectedWatermark->setText(watermark->getFilename());
		selectedWatermark->center(winInfo.w, pane->getY());
	}
	selectedWatermark->draw();
}

} /* namespace ConsoleArt */
