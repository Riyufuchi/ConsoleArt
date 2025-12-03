//==============================================================================
// File       : ControllerSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Dec 03, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "ControllerSDL.h"

namespace consoleart
{
ControllerSDL::ControllerSDL() : Controller(new NotifierSDL(), nullptr, new AsciiPrinterSDL(new NotifierSDL())), width(800), height(600)
{
	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow(
			consoleart::GeneralTools::CONSOLE_ART_VERSION,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_SetWindowMinimumSize(window, 400, 300);
	setAppIcon();
	this->renderer = SDL_CreateRenderer(window, 0,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		isRunnable = false;
		return;
	}
	setenv("TINYFD_FORCE_XDG", "1", 1);
	this->buttons = new ButtonBuilder(renderer);
	winInfo.w = width;
	winInfo.h = height;
	winInfo.mouseX = 0;
	winInfo.mouseY = 0;
	winInfo.keepRunning = isRunnable;
	winInfo.window = window;
	winInfo.renderer = renderer;
	this->stateManager = new StateManager(currentState);
	this->currentState = new MainStateSDL(winInfo, *buttons, *this, *stateManager);
	this->stateManager->addNewState(WindowState::MAIN, currentState);
	this->stateManager->addNewState(WindowState::EDIT_IMAGE, new EditImageStateSDL(winInfo, *buttons, *this, *stateManager));
	this->stateManager->addNewState(WindowState::SHOW_IMAGE, new ImageStateSDL(winInfo, *this, *stateManager));
	this->stateManager->addNewState(WindowState::SELECT_IMAGE, new SelectImageStateSDL(winInfo, *this, *stateManager, *buttons));
	this->stateManager->addNewState(WindowState::ABOUT, new AboutStateSDL(winInfo, *this, *stateManager, *buttons));
	this->stateManager->addNewState(WindowState::ASCII_CONVERTER, new AsciiConvertStateSDL(winInfo, *this, *stateManager, *buttons));
	this->stateManager->addNewState(WindowState::WATERMARK, new WatermarkStateSDL(winInfo, *this, *stateManager, *buttons));
	this->stateManager->addNewState(WindowState::FILTER_IMAGE, new ImageFilterStateSDL(winInfo, *this, *stateManager));
	this->stateManager->addNewState(WindowState::CONFIG, new ConfigStateSDL(winInfo, *this, *stateManager, *buttons));
}

ControllerSDL::~ControllerSDL()
{
	if (buttons)
	{
		delete buttons;
		buttons = nullptr;
	}
	if (stateManager)
	{
		delete stateManager;
		stateManager = nullptr;
	}
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
void ControllerSDL::run()
{
	if (!isRunnable)
		return;
	if (!buttons->isReady())
		return;

	#ifdef DEBUG
		SDL_RendererInfo info;
		SDL_GetRendererInfo(renderer, &info);

		int numRenderDrivers = SDL_GetNumRenderDrivers();
		std::cout << "Available render drivers: " << numRenderDrivers << std::endl;
		for (int i = 0; i < numRenderDrivers; ++i)
		{
			std::cout << "Driver " << i << ": " << info.name << std::endl;
		}
	#endif

	//const int targetFPS = 360;
	//const int frameDelay = 1000 / targetFPS; // Milliseconds per frame
	//unsigned int frameStart = 0;
	//unsigned int frameTime = 0;

	while (winInfo.keepRunning)
	{
		//frameStart = SDL_GetTicks();
		// Handle events
		SDL_GetMouseState(&winInfo.mouseX, &winInfo.mouseY);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				winInfo.keepRunning = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					winInfo.w = event.window.data1;
					winInfo.h = event.window.data2;
					SDL_RenderSetLogicalSize(renderer, winInfo.w, winInfo.h);
					currentState->onWindowResize();
				}
				break;
			default:
				currentState->handleTick(event);
				break;
			}
		}
		// Rendering
		SDL_RenderClear(renderer); // Clear window
		currentState->render(); // Render content
		SDL_RenderPresent(renderer); // Present content
		// Frame rate control
		/*frameTime = SDL_GetTicks() - frameStart; // Calculate frame duration
		if (frameTime < frameDelay)
		{
		SDL_Delay(frameDelay - frameTime); // Delay only if needed
		}
		else
		{
		SDL_Log("Warning: Frame took too long! %u ms\n", frameTime);
		}*/
	}
}
void ControllerSDL::setAppIcon()
{
	if (!window)
		return;

	int w, h, channels;
	unsigned char* pixels = stbi_load_from_memory(icon_png, icon_png_len, &w, &h, &channels, 4);

	if (!pixels)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "stb failed load from memory: %s", stbi_failure_reason());
		return;
	}

	// Wrap stb pixels into a temporary SDL surface (NO COPY!)
	SDL_Surface* tempSurface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 32, w * 4, SDL_PIXELFORMAT_RGBA32);

	if (!tempSurface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to wrap surface: %s", SDL_GetError());
		stbi_image_free(pixels);
		return;
	}

	SDL_Surface* icon = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32, 0);
	if (!icon)
	{
		SDL_Log("Failed to load icon: %s", SDL_GetError());
		return;
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;
	stbi_image_free(pixels);
	pixels = nullptr;

	SDL_SetWindowIcon(window, icon); // Set the icon
	SDL_FreeSurface(icon); // Free the surface (no longer needed)
	icon = nullptr;
}

Controller::IndexDataType ControllerSDL::selectImageMenu()
{
	return 0;
}

void ControllerSDL::showAboutApplicationInfo()
{
}

std::string ControllerSDL::inputImageName()
{
	std::vector<std::string> formatStrings;
	std::vector<char*> formatCStrs;
	for (const auto& p : supportedImageFormats)
	{
		formatStrings.push_back("*" + p.first);
		formatCStrs.push_back(strdup(formatStrings.back().c_str())); // Duplicate for C compatibility
	}
	const char* result = tinyfd_openFileDialog("Select an Image", workspacePath.c_str(), formatCStrs.size(), formatCStrs.data(), "Image Files", 0);
	if (result)
		return std::string(result);
	return "";
}

} /* namespace consoleart */
