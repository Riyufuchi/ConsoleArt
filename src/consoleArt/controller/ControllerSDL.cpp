//==============================================================================
// File       : ControllerSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
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
	this->sheet = new SpriteSheet("UI.png", renderer);
	std::string B1 = "PlayBtn";
	std::string B2 = "PlayBtnHover";
	this->sheet->prepareTexture(B1, 0, 0, 64, 32);
	this->sheet->prepareTexture(B2, 64, 0, 64, 32);
	this->button = new ButtonSDL(0, 0, 200, 100);
	this->button->setX((width / 2) - button->getWidth() / 2);
	this->button->setY((height / 2) - button->getHeight() / 2);
	this->imgButton = new ImageButtonSDL(16, 16, 200, 100, sheet->getTexture(B2), sheet->getTexture(B1));
}

ControllerSDL::~ControllerSDL()
{
	delete sheet;
	sheet = 0;
	delete button;
	button = 0;
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

		button->setMouseOver(button->isMouseInside(mouseX, mouseY));
		imgButton->setMouseOver(imgButton->isMouseInside(mouseX, mouseY));

		switch (event.type)
		{
			case SDL_QUIT: isRunnable = false; break;
			case SDL_MOUSEBUTTONDOWN:
				if (button->isMouseOver())
					std::cout << "Button Clicked!" << std::endl;
			break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					width = event.window.data1;
					height = event.window.data2;
					//SDL_Log("Window resized to %dx%d", width, height);

					// (Optional) Adjust renderer size if needed
					SDL_RenderSetLogicalSize(renderer, width, height);
					button->setX((width / 2) - button->getWidth() / 2);
					button->setY((height / 2) - button->getHeight() / 2);
				}
			break;
		}

		// Rendering
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);  // R, G, B, A (0-255)
		SDL_RenderClear(renderer);

		button->draw(renderer);
		imgButton->draw(renderer);

		SDL_RenderPresent(renderer);

		// Frame rate control
		frameTime = SDL_GetTicks() - frameStart; // Calculate frame duration
		if (frameTime > frameDelay)
		{
			SDL_Delay(frameDelay - frameTime); // Delay to maintain 60 FPS
		}
	}
}

} /* namespace ConsoleArt */
