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
	setenv("TINYFD_FORCE_XDG", "1", 1);
	winInfo.w = width;
	winInfo.h = height;
	winInfo.mouseX = 0;
	winInfo.mouseY = 0;
	winInfo.keepRunning = isRunnable;
	currentState = new MainState(renderer, stateController, winInfo, messenger);
}

ControllerSDL::~ControllerSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
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

	while (winInfo.keepRunning)
	{
		frameStart = SDL_GetTicks();
		// Handle events
		SDL_PollEvent(&event);
		SDL_GetMouseState(&winInfo.mouseX, &winInfo.mouseY);
		currentState->handleTick(event);
		switch (event.type)
		{
			case SDL_QUIT: winInfo.keepRunning = false; break;
		}

		// Rendering
		currentState->render();
		SDL_RenderPresent(renderer);

		// Frame rate control
		frameTime = SDL_GetTicks() - frameStart; // Calculate frame duration
		if (frameTime > frameDelay)
		{
			SDL_Delay(frameDelay - frameTime); // Delay to maintain 60 FPS
		}
	}
}

void ControllerSDL::configure(std::map<std::string, std::vector<std::string>>& config)
{
}

} /* namespace ConsoleArt */
