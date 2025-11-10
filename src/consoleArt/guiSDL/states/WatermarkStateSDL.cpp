//==============================================================================
// File       : WatermarkStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 8, 2025
// Last edit  : Nov 10, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "WatermarkStateSDL.h"

namespace ConsoleArt
{
WatermarkStateSDL::WatermarkStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons), y(0)
{
	this->watermark = nullptr;
	this->textUpdated = false;
	this->selectedWatermark = new sdl::LabelSDL("No watermark selected", FONT_SECONDARY, SIZE, BASE_TEXT_COLOR, renderer);
	this->imageNameLabel = new sdl::LabelSDL("", FONT_SECONDARY, SIZE, BASE_TEXT_COLOR, renderer);
	this->mainPane = new sdl::ContentPanelSDL();
	this->mainPane->addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::SELECT, true), [&]() { selectWatermarkEvent(); }));
	this->mainPane->addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::APPLY, true), [&]() { std::thread([&](){ applytWatermarkEvent(); }).detach(); }));
	this->mainPane->addComponent(1, new sdl::ImageButtonSDL(256, 128, buttons.getButtonTextureFor(ButtonType::BACK, false), [&]() { stateManager.switchState(WindowState::EDIT_IMAGE); }));
	this->pane = mainPane;
	this->selectPane = new sdl::ContentPanelSDL();
	this->selectPane->addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::APPLY, true), [&]() { pane = mainPane; }));
	onWindowResize();
}

WatermarkStateSDL::~WatermarkStateSDL()
{
	delete mainPane;
	delete selectPane;
	delete selectedWatermark;
	delete imageNameLabel;
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
	selectedWatermark->center(winInfo.w, pane->getY() - imageNameLabel->getHeight());
	imageNameLabel->center(winInfo.w, pane->getY() + selectedWatermark->getHeight());
}

void WatermarkStateSDL::onReturn()
{
	if (!watermark)
		selectedWatermark->setText("No watermark selected");
	imageNameLabel->setText("For image: " + controller.getSelectedImage()->getFilename());
	onWindowResize();
}

void WatermarkStateSDL::selectWatermarkEvent()
{
	if (controller.getNumberOfLoadedImages() < 2)
	{
		selectedWatermark->setText("No images to select from");
		textUpdated = true;
		return;
	}
	watermark = nullptr;
	textUpdated = true;
	selectPane->clear();
	y = 0;
	controller.iterateImagesAsync([&](Images::Image* image)
	{
		Images::Image* imgCopy = image;
		selectPane->addComponent(y, new sdl::StringButtonSDL(0, 0,
		new sdl::StringSDL(image->getFilename(), FONT_SECONDARY, SIZE, BASE_TEXT_COLOR, renderer), HOVER_TEXT_COLOR,
		[imgCopy, this]()
		{
			watermark = imgCopy;
			textUpdated = true;
			pane = mainPane;
		}));
		y++;
	});
	pane = selectPane;
	selectedWatermark->setText("Select watermark");
	onWindowResize();
}

void WatermarkStateSDL::applytWatermarkEvent()
{
	if (watermark && ImageUtils::ImageTools::signatureToImage(*controller.getSelectedImage(), *watermark))
		controller.notifyUser(AbstractNotifier::SUCCESFUL_TASK, "Watermark successfully applied to the image.");
}

void WatermarkStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane->draw(renderer);
	if (textUpdated)
	{
		textUpdated = false;
		if (watermark)
			selectedWatermark->setText(watermark->getFilename());
		selectedWatermark->center(winInfo.w, pane->getY() - imageNameLabel->getHeight());
	}
	selectedWatermark->draw();
	imageNameLabel->draw();
}

} /* namespace ConsoleArt */
