//==============================================================================
// File       : ControllerSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ControllerSDL.h"

namespace ConsoleArt
{
ControllerSDL::ControllerSDL() : Controller(new NotifierSDL(), nullptr, nullptr), width(800), height(600)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() == -1)
	{
		SDL_Log("ERROR: Failed to initialize SDL_ttf: %s", TTF_GetError());
	}
	this->window = SDL_CreateWindow(("ConsoleArt v" + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION)).c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	this->selectedImageString = new StringSDL("A\nB", "TF2Build.ttf", 24, {255, 105, 180, 255}, renderer);
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
	this->sheet = new SpriteSheet("ui.png", renderer);
	this->sheet->prepareTexturePair(addImageBtn, 0, 0, rectangle);
	this->sheet->prepareTexturePair(exitBtn, 0, 160, square);
	this->sheet->prepareTexturePair(configBtn, 0, 96, square);
	this->sheet->prepareTexturePair(selectBtn, 0, 32, rectangle);
	this->sheet->prepareTexturePair(asyncBtn, 128, 0, square);
	this->sheet->prepareTexturePair(editBtn, 128, 32, square);
	this->sheet->prepareTexturePair(aboutBtn, 128, 64, square);
	this->pane = new ContentPanelSDL(0, 0);
	// 0
	pane->addComponent(0, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexturePair(addImageBtn), [&](){ addImageButtonEvent(); }));
	pane->addComponent(0, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(asyncBtn), [&]() { std::thread([&](){ loadAllImagesAsync(); }).detach(); }));
	// 1
	pane->addComponent(1, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexturePair(selectBtn)));
	pane->addComponent(1, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(editBtn)));
	// 2
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(configBtn)));
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(aboutBtn), [&]() { showAboutApplicationInfo(); }));
	pane->addComponent(2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(exitBtn), [&]() { isRunnable = false; }));
	pane->setX((width / 2) - pane->getWidth() / 2);
	pane->setY((height / 2) - pane->getHeight() / 2);
	pane->reposeContent();
	setenv("TINYFD_FORCE_XDG", "1", 1);
	textUpdated = false;
	font = selectedImageString->getFont();
}

ControllerSDL::~ControllerSDL()
{
	delete sheet;
	delete pane;
	delete selectedImageString;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

void ControllerSDL::addImageButtonEvent()
{
	std::thread([&]()
	{
		Images::Image* img = loadImageAsync(inputImageName());
		if (addImageAsync(img))
		{
			messenger->messageUser("Image successfully loaded.");
			selectedImage = img;
			textUpdated = true;
		}
	}).detach();
}

void ControllerSDL::run()
{
	SDL_RendererInfo info;
	SDL_GetRendererInfo(renderer, &info);

	int numRenderDrivers = SDL_GetNumRenderDrivers();
	std::cout << "Available render drivers: " << numRenderDrivers << std::endl;
	for (int i = 0; i < numRenderDrivers; ++i)
	{
		std::cout << "Driver " << i << ": " << info.name << std::endl;
	}

	SDL_Event event;
	const int targetFPS = 60;
	const int frameDelay = 1000 / targetFPS; // Milliseconds per frame
	unsigned int frameStart = 0;
	unsigned int frameTime = 0;
	int mouseX, mouseY;

	while (isRunnable)
	{
		frameStart = SDL_GetTicks();
		// Handle events
		SDL_PollEvent(&event);
		SDL_GetMouseState(&mouseX, &mouseY);

		pane->checkHoverOverContent(mouseX, mouseY);
		//button->setMouseOver(button->isMouseInside(mouseX, mouseY));
		//imgButton->setMouseOver(imgButton->isMouseInside(mouseX, mouseY));

		switch (event.type)
		{
			case SDL_QUIT: isRunnable = false; break;
			case SDL_MOUSEBUTTONDOWN:
				pane->tickOnClick();
				/*if (button->isMouseOver())
					std::cout << "Button Clicked!" << std::endl;*/
			break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					width = event.window.data1;
					height = event.window.data2;
					//SDL_Log("Window resized to %dx%d", width, height);

					// (Optional) Adjust renderer size if needed
					SDL_RenderSetLogicalSize(renderer, width, height);
					pane->setX((width / 2) - pane->getWidth() / 2);
					pane->setY((height / 2) - pane->getHeight() / 2);
					pane->reposeContent();
					selectedImageString->repose((width / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
				}
			break;
		}

		// Rendering
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
		SDL_RenderClear(renderer);

		pane->draw(renderer);
		if (textUpdated && selectedImage)
		{
			textUpdated = false;
			selectedImageString->setText(std::string("Selected image: ").append(selectedImage->getFilename()));
			selectedImageString->repose((width / 2) - (selectedImageString->getWidth() / 2), (pane->getY() / 2) - (selectedImageString->getHeight() / 2));
		}
		selectedImageString->draw(renderer);

		SDL_RenderPresent(renderer);

		// Frame rate control
		frameTime = SDL_GetTicks() - frameStart; // Calculate frame duration
		if (frameTime > frameDelay)
		{
			SDL_Delay(frameDelay - frameTime); // Delay to maintain 60 FPS
		}
	}
}

void ControllerSDL::showAboutApplicationInfo()
{
}

std::string ControllerSDL::inputImageName()
{
	std::vector<std::string> formatStrings;
	std::vector<char*> formatCStrs;
	for (const auto& p : suppertedImageFormats)
	{
		formatStrings.push_back("*" + p.first);
		formatCStrs.push_back(strdup(formatStrings.back().c_str())); // Duplicate for C compatibility
	}
	const char* result = tinyfd_openFileDialog("Select an Image", workspacePath.c_str(), formatCStrs.size(), formatCStrs.data(), "Image Files", 0);
	if (result)
		return std::string(result);
	return "";
}

void ControllerSDL::configure(std::map<std::string, std::vector<std::string>>& config)
{
}


Images::Image* ControllerSDL::selectImage()
{
	return nullptr;
}

void ControllerSDL::refreshMenu() {
}

} /* namespace ConsoleArt */
