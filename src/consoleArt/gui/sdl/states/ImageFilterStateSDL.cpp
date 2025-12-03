//==============================================================================
// File       : ImageFilterStateSDL.cpp
// Author     : riyufuchi
// Created on : May 24, 2025
// Last edit  : Dec 03, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageFilterStateSDL.h"

namespace ConsoleArt
{

ImageFilterStateSDL::ImageFilterStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager) : StateSDL(winInfo), AbstractState(controller, stateManager)
{
	int y = 0;
	for (const std::string& text : FILTER_TEXTS)
	{
		pane.addComponent(y, new sdl::StringButtonSDL(new sdl::TextSDL(renderer, FONT_BASE, text, 32, BASE_TEXT_COLOR ),
				HOVER_TEXT_COLOR, [&](){ applyFilterEvent(text); }));
		y++;
	}
	pane.addComponent(y, new sdl::StringButtonSDL(new sdl::TextSDL(renderer, FONT_BASE, "Back", 32, BASE_TEXT_COLOR ),
		HOVER_TEXT_COLOR, [&](){ stateManager.switchState(WindowState::EDIT_IMAGE); }));
	onWindowResize();
}

bool ImageFilterStateSDL::applyFilter(const std::string& filter)
{
	if (controller.getSelectedImage() == nullptr)
	{
		controller.notifyUser(AbstractNotifier::MessageType::ERROR, "Error: No image selected!");
		return false;
	}

	int y = 0;

	for (const std::string& text : FILTER_TEXTS)
	{
		if (text == filter)
			break;
		y++;
	}

	switch (y)
	{
		case 0: return ImageUtils::Filter::matrixFilter(*controller.getSelectedImage());
		case 1: return ImageUtils::Filter::purplefier(*controller.getSelectedImage());
		case 2: return ImageUtils::Filter::purplefierSoft(*controller.getSelectedImage());
		case 3: return ImageUtils::Filter::purplefierShading(*controller.getSelectedImage());
		case 4: return ImageUtils::Filter::purplefierShadingSoft(*controller.getSelectedImage());
		default:
			controller.notifyUser(AbstractNotifier::MessageType::ERROR, "Error: Invalid filter selection!");
		return false;
	}
}

void ImageFilterStateSDL::applyFilterEvent(std::string filter)
{
	controller.notifyUser(AbstractNotifier::MessageType::INFO, "Applying filter in the background."); // This is non-blocking dialog
	std::thread([this, filter]()
	{
		if (applyFilter(filter))
			controller.notifyUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Filter successfully applied.");
		else
			controller.notifyUser(AbstractNotifier::MessageType::ERROR, "Filter application failed during saving the image.");
	}).detach();
}

void ImageFilterStateSDL::onReturn()
{
	onWindowResize();
}

void ImageFilterStateSDL::handleTick(SDL_Event& event)
{
	pane.checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane.tickOnClick(); break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: stateManager.switchState(WindowState::MAIN); break;
			}
		break;
	}
}

void ImageFilterStateSDL::onWindowResize()
{
	pane.center(winInfo.w, winInfo.h);
	pane.reposeContent();
}

void ImageFilterStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
}

} /* namespace ConsoleArt */
