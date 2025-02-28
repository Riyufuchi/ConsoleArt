//==============================================================================
// File       : ControllerSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 27, 2025
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
	this->window = SDL_CreateWindow(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	setenv("TINYFD_FORCE_XDG", "1", 1);
	winInfo.w = width;
	winInfo.h = height;
	winInfo.mouseX = 0;
	winInfo.mouseY = 0;
	winInfo.keepRunning = isRunnable;
	this->textUpdated = false;
	currentState = new MainState(renderer, winInfo, [&]() { addImageButtonEvent(); }, [&]() { std::thread([&](){ loadAllImagesAsync(); }).detach(); },
			[&](StringSDL* strSDL) { return updateString(strSDL); });
}

ControllerSDL::~ControllerSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

bool ControllerSDL::updateString(StringSDL* stringSDL)
{
	if (textUpdated && selectedImage && stringSDL)
	{
		textUpdated = false;
		stringSDL->setText(std::string("Selected image: ").append(selectedImage->getFilename()));
		return true;
	}
	return false;
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

Images::Image* ControllerSDL::selectImage()
{
	return nullptr;
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

} /* namespace ConsoleArt */
