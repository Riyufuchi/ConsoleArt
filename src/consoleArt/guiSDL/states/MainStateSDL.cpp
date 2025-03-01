//==============================================================================
// File       : MainStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MainStateSDL.h"

namespace ConsoleArt
{
MainStateSDL::MainStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, std::function<void()> switchState) : sdl::StateSDL(winInfo), buttons(buttons), controller(controller)
{
	this->textUpdated = false;
	this->selectedImageString = new sdl::StringSDL("No image selected", "TF2Build.ttf", 24, {255, 105, 180, 255}, renderer);
	this->selectedImageString->setY(16);
	this->pane = new sdl::ContentPanelSDL(0, 0);
	// 0
	pane->addComponent(0, new sdl::ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::LOAD, false), [&]() { addImageButtonEvent(); }));
	pane->addComponent(0, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::LOAD_ALL, true), [&]() { std::thread([&](){ controller.loadAllImagesAsync(); }).detach(); }));
	// 1
	pane->addComponent(1, new sdl::ImageButtonSDL(0, 0, 200, 100, buttons.getButtonTextureFor(ButtonType::SELECT_IMAGE, false)));
	pane->addComponent(1, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::EDIT_IMAGE, true), switchState));
	// 2
	pane->addComponent(2, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::SETTINGS, true)));
	pane->addComponent(2, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::ABOUT, true), [&]() {  }));
	pane->addComponent(2, new sdl::ImageButtonSDL(0, 0, 100, 100, buttons.getButtonTextureFor(ButtonType::EXIT, true), [&]() { exitApplication(); }));
	pane->setX((winInfo.w / 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
	this->font = selectedImageString->getFont();
	selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
}

MainStateSDL::~MainStateSDL()
{
	delete pane;
	delete selectedImageString;
}

bool MainStateSDL::updateString(sdl::StringSDL* stringSDL)
{
	if (textUpdated && controller.getSelectedImage() && stringSDL)
	{
		textUpdated = false;
		stringSDL->setText(std::string("Selected image: ").append(controller.getSelectedImage()->getFilename()));
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

void MainStateSDL::handleTick(SDL_Event &event)
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
		case SDL_DROPFILE:
		{
			std::thread([&]()
			{
				char* droppedFile = event.drop.file;
				if (droppedFile)
				{
					std::string filePath(droppedFile);
					SDL_Log("%s", filePath.c_str());
					Images::Image* img = controller.loadImageAsync(filePath);
					if (controller.addImageAsync(img))
					{
						controller.getMessenger().messageUser("Image successfully loaded.");
						controller.setSelectedImage(img);
						textUpdated = true;
					}
					else
						controller.getMessenger().messageUser("Image unsuccessfully loaded.");
					SDL_free(droppedFile);  // Free the allocated string
				}
			}).detach(); // Your existing loading logic
		}
		break;
	}
}

void MainStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
	pane->draw(renderer);
	if (updateString(selectedImageString))
		selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
	selectedImageString->draw(renderer);
}

void MainStateSDL::onReturn()
{
	pane->setX((winInfo.w/ 2) - pane->getWidth() / 2);
	pane->setY((winInfo.h / 2) - pane->getHeight() / 2);
	pane->reposeContent();
	selectedImageString->repose((winInfo.w / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
}

} /* namespace ConsoleArt */
