//==============================================================================
// File       : MainStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Nov 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "MainStateSDL.h"

namespace consoleart
{
MainStateSDL::MainStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, StateManager& stateManager) : sdl::StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	this->textUpdated = false;
	this->selectedImageString = new sdl::LabelSDL("No image selected", FONT_SECONDARY, 24, {255, 105, 180, 255}, renderer);
	this->selectedImageString->setY(16);
	// 0
	this->pane.addComponent(0, new sdl::ImageButtonSDL(256, 128, buttons.getButtonTextureFor(ButtonType::LOAD, false), [&]() { addImageButtonEvent(); }));
	this->pane.addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::LOAD_ALL, true), [&]() { std::thread([&](){ controller.loadAllImagesAsync(); }).detach(); }));
	this->pane.addComponent(0, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::IMAGE_INFO, true), [&]()
	{
		if (controller.getSelectedImage())
			controller.displayImageInfo(*controller.getSelectedImage());
	}));
	// 1
	this->pane.addComponent(1, new sdl::ImageButtonSDL(256, 128, buttons.getButtonTextureFor(ButtonType::SELECT_IMAGE, false), [&]()
	{
		if (controller.getNumberOfLoadedImages()) // There has to be at least one image loaded
			stateManager.switchState(WindowState::SELECT_IMAGE);
		else
			controller.notifyUser(AbstractNotifier::MessageType::WARNING, "No images to select from!");
	}));
	this->pane.addComponent(1, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::EDIT_IMAGE, true), [&]()
	{
		controller.getSelectedImage() ?
		stateManager.switchState(WindowState::EDIT_IMAGE) :
		controller.notifyUser(AbstractNotifier::MessageType::WARNING, "No image selected!");
	}));
	this->pane.addComponent(1, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::SHOW_IMAGE, true), [&]()
	{
		controller.getSelectedImage() ?
		stateManager.switchState(WindowState::SHOW_IMAGE) :
		controller.notifyUser(AbstractNotifier::MessageType::WARNING, "No image selected!");
	}));
	// 2
	this->pane.addComponent(2, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::SETTINGS, true), [&]()
	{
		stateManager.switchState(WindowState::CONFIG);
	}));
	this->pane.addComponent(2, new sdl::ImageButtonSDL(128, 128, buttons.getButtonTextureFor(ButtonType::ABOUT, true), [&]() { stateManager.switchState(WindowState::ABOUT); }));
	this->pane.addComponent(2, new sdl::ImageButtonSDL(256, 128, buttons.getButtonTextureFor(ButtonType::EXIT, false), [&]() { exitApplication(); }));
	onReturn();
}

MainStateSDL::~MainStateSDL()
{
	if (selectedImageString)
	{
		delete selectedImageString;
		selectedImageString = nullptr;
	}
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
		Controller::IndexDataType id = controller.addImageAsync(controller.loadImageAsync(controller.inputImageName()));
		if (id)
		{
			controller.notifyUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Image successfully loaded.");
			controller.selectImage(id);
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
		#ifdef DEBUGtextUpdated
			SDL_Log("%s", filePath.c_str());
		#endif
		Controller::IndexDataType id = controller.addImageAsync(controller.loadImageAsync(filePath));
		if (id)
		{
			controller.notifyUser(AbstractNotifier::SUCCESFUL_TASK, "Image successfully loaded.");
			controller.selectImage(id);
			textUpdated = true;
		}
		else
		{
			controller.notifyUser(AbstractNotifier::ERROR, "Image failed to load.");
		}
		SDL_free(droppedFile);
	}).detach();
}

void MainStateSDL::handleTick(SDL_Event &event)
{
	pane.checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane.tickOnClick(); break;
		case SDL_DROPFILE: loadDropedFile(event.drop.file); break;
	}
}

void MainStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
	if (updateString(selectedImageString))
		selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane.getY() / 2) - (selectedImageString->getHeight() / 2));
	selectedImageString->draw(renderer);
}

void MainStateSDL::onReturn()
{
	pane.center(winInfo.w, winInfo.h);
	pane.reposeContent();
	textUpdated = true; // Update text if another image was selected
	selectedImageString->center(winInfo.w, pane.getY());
}

void MainStateSDL::onWindowResize()
{
	SDL_RenderSetLogicalSize(renderer, winInfo.w, winInfo.h);
	onReturn();
}

} /* namespace consoleart */
