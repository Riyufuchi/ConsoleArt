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

ControllerSDL::ControllerSDL(ConsoleLib::UnixConsole& console) : ControllerZenity(&console), width(800), height(600)
{
	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow(("ConsoleArt v" + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION)).c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
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
	pane->addComponent(0, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexturePair(addImageBtn)));
	pane->addComponent(0, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexturePair(asyncBtn), [&]() { loadAllImagesAsync(); }));
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
}

ControllerSDL::~ControllerSDL()
{
	delete sheet;
	delete pane;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
				}
			break;
		}

		// Rendering
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
		SDL_RenderClear(renderer);

		pane->draw(renderer);

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
	std::thread([&](){ ControllerZenity::showAboutApplicationInfo(); }).detach();
}

} /* namespace ConsoleArt */
