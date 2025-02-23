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
	std::string AddImageBtn = "1";
	std::string AddImageBtnHover = "1H";
	std::string ExitBtn = "2";
	std::string ExitBtnHover = "2H";
	std::string ConfigBtn = "3";
	std::string ConfigBtnHover = "3H";
	std::string SelectBtn = "4";
	std::string SelectBtnHover = "4H";
	this->sheet->prepareTexture(AddImageBtnHover, 0, 0, 64, 32);
	this->sheet->prepareTexture(AddImageBtn, 64, 0, 64, 32);

	this->sheet->prepareTexture(ExitBtnHover, 0, 96, 32, 32);
	this->sheet->prepareTexture(ExitBtn, 32, 96, 32, 32);

	this->sheet->prepareTexture(ConfigBtnHover, 0, 160, 32, 32);
	this->sheet->prepareTexture(ConfigBtn, 32, 160, 32, 32);

	this->sheet->prepareTexture(SelectBtnHover, 0, 32, 64, 32);
	this->sheet->prepareTexture(SelectBtn, 64, 32, 64, 32);
	//this->button = new ButtonSDL(0, 0, 200, 100);
	//this->button->setX((width / 2) - button->getWidth() / 2);
	//this->button->setY((height / 2) - button->getHeight() / 2);
	this->pane = new ContentPanelSDL(0, 0, 0, 0, 0);
	pane->addComponent(0, 0, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexture(AddImageBtn), sheet->getTexture(AddImageBtnHover)));
	pane->addComponent(0, 1, new ImageButtonSDL(0, 0, 200, 100, sheet->getTexture(SelectBtn), sheet->getTexture(SelectBtnHover)));
	pane->addComponent(0, 2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexture(ExitBtn), sheet->getTexture(ExitBtnHover)));
	pane->addComponent(1, 2, new ImageButtonSDL(0, 0, 100, 100, sheet->getTexture(ConfigBtn), sheet->getTexture(ConfigBtnHover)));
	pane->setX((width / 2) - pane->getWidth() / 2);
	pane->setY((height / 2) - pane->getHeight() / 2);
	pane->repose();
}

ControllerSDL::~ControllerSDL()
{
	delete sheet;
	sheet = 0;
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

		pane->checkHover(mouseX, mouseY);
		//button->setMouseOver(button->isMouseInside(mouseX, mouseY));
		//imgButton->setMouseOver(imgButton->isMouseInside(mouseX, mouseY));

		switch (event.type)
		{
			case SDL_QUIT: isRunnable = false; break;
			case SDL_MOUSEBUTTONDOWN:
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
					pane->repose();
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

} /* namespace ConsoleArt */
