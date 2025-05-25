//==============================================================================
// File       : ImageFilterStateSDL.cpp
// Author     : riyufuchi
// Created on : May 24, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageFilterStateSDL.h"

namespace ConsoleArt
{

ImageFilterStateSDL::ImageFilterStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager) : StateSDL(winInfo), AbstractState(controller, stateManager)
{
	pane.addComponent(0, new sdl::StringButtonSDL(new sdl::StringSDL("Matrix", FONT_BASE, 32, BASE_TEXT_COLOR, renderer), HOVER_TEXT_COLOR, [&]() { applyFilterEvent(Filter::MATRIX); }));
	pane.addComponent(1, new sdl::StringButtonSDL(new sdl::StringSDL("Back", FONT_BASE, 32, BASE_TEXT_COLOR, renderer), HOVER_TEXT_COLOR, [&]() { stateManager.switchState(WindowState::EDIT_IMAGE); }));
	onWindowResize();
}

bool ImageFilterStateSDL::applyFilter(Filter filter)
{
	if (controller.getSelectedImage() == nullptr)
		return false;

	switch (filter)
	{
		case MATRIX: return ImageUtils::Filter::matrixFilter(*controller.getSelectedImage());
		default: return false;
	}
}

void ImageFilterStateSDL::applyFilterEvent(Filter filter)
{
	std::thread([&]()
	{
		controller.getMessenger().messageUser(AbstractNotifier::MessageType::INFO,"Applying filter in the background.");
		if (applyFilter(filter))
		{
			controller.getMessenger().messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK,"Filter successfully applied.");
		}
	}
	).detach();
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
