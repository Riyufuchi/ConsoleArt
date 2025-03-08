//==============================================================================
// File       : MainStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Mar 8, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MainStateSDL.h"

namespace ConsoleArt
{
MainStateSDL::MainStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, StateManager& stateManager) : sdl::StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	this->textUpdated = false;
	this->selectedImageString = new sdl::LabelSDL("No image selected", "TF2secondary.ttf", 24, {255, 105, 180, 255}, renderer);
	this->selectedImageString->setY(16);
	this->pane = new sdl::ContentPanelSDL(0, 0);
	// 0
	pane->addComponent(0, new sdl::ImageButtonSDL(200, 100, buttons.getButtonTextureFor(ButtonType::LOAD, false), [&]() { addImageButtonEvent(); }));
	pane->addComponent(0, new sdl::ImageButtonSDL(100, 100, buttons.getButtonTextureFor(ButtonType::LOAD_ALL, true), [&]() { std::thread([&](){ controller.loadAllImagesAsync(); }).detach(); }));
	// 1
	pane->addComponent(1, new sdl::ImageButtonSDL(200, 100, buttons.getButtonTextureFor(ButtonType::SELECT_IMAGE, false), [&]() { stateManager.switchState(WindowState::SELECT_IMAGE); }));
	pane->addComponent(1, new sdl::ImageButtonSDL(100, 100, buttons.getButtonTextureFor(ButtonType::EDIT_IMAGE, true), [&]()
	{
		controller.getSelectedImage() ?
		stateManager.switchState(WindowState::EDIT_IMAGE) :
		std::thread([&](){ controller.getMessenger().messageUser(AbstractNotifier::MessageType::WARNING, "No image selected!"); }).detach();
	}));
	// 2
	pane->addComponent(2, new sdl::ImageButtonSDL(100, 100, buttons.getButtonTextureFor(ButtonType::SETTINGS, true), [&]() { std::thread([&](){ controller.getMessenger().messageUser(AbstractNotifier::WARNING, "Not yet implemented."); }).detach(); }));
	pane->addComponent(2, new sdl::ImageButtonSDL(100, 100, buttons.getButtonTextureFor(ButtonType::ABOUT, true), [&]() { stateManager.switchState(WindowState::ABOUT); }));
	pane->addComponent(2, new sdl::ImageButtonSDL(100, 100, buttons.getButtonTextureFor(ButtonType::EXIT, true), [&]() { exitApplication(); }));
	this->font = selectedImageString->getFont();
	onReturn();
}

MainStateSDL::~MainStateSDL()
{
	delete pane;
	delete selectedImageString;
}

bool MainStateSDL::updateString(sdl::LabelSDL* stringSDL)
{
	if (textUpdated && controller.getSelectedImage() && stringSDL)
	{
		textUpdated = false;
		stringSDL->setText(controller.getSelectedImage()->getFilename());
		return true;
	}
	return false;
}

void MainStateSDL::addImageButtonEvent()
{
	std::thread([&]()
	{
		Images::Image* img = controller.loadImageAsync(controller.inputImageName());
		if (controller.addImageAsync(img))
		{
			controller.getMessenger().messageUser("Image successfully loaded.");
			controller.setSelectedImage(img);
			textUpdated = true;
		}
	}).detach();
}

void MainStateSDL::loadDropedFile(char* droppedFile)
{
	if (!droppedFile)
		return;
	std::thread([filePath = std::string(droppedFile), droppedFile, this]()
	{
		SDL_Log("%s", filePath.c_str());
		Images::Image* img = controller.loadImageAsync(filePath);
		if (controller.addImageAsync(img))
		{
			controller.getMessenger().messageUser("Image successfully loaded.");
			controller.setSelectedImage(img);
			textUpdated = true;
		}
		else
		{
			controller.getMessenger().messageUser("Image unsuccessfully loaded.");
		}
		SDL_free(droppedFile);
	}).detach();
}

void MainStateSDL::handleTick(SDL_Event &event)
{
	pane->checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane->tickOnClick(); break;
		case SDL_DROPFILE: loadDropedFile(event.drop.file); break;
	}
}

void MainStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane->draw(renderer);
	if (updateString(selectedImageString))
		selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
	selectedImageString->draw(renderer);
}

void MainStateSDL::onReturn()
{
	pane->center(winInfo.w, winInfo.h);
	pane->reposeContent();
	selectedImageString->center(winInfo.w, pane->getY());
}

void MainStateSDL::onWindowResize()
{
	SDL_RenderSetLogicalSize(renderer, winInfo.w, winInfo.h);
	onReturn();
}

} /* namespace ConsoleArt */
