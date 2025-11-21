//==============================================================================
// File       : SelectImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 03, 2025
// Last edit  : May 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiConvertStateSDL.h"

namespace ConsoleArt
{
AsciiConvertStateSDL::AsciiConvertStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractAciiConversionState(controller, stateManager), buttons(buttons)
{
	const int SIZE = 32;
	//
	this->y = 0;
	for (const auto& textPair : texts)
	{
		pane.addComponent(y, new sdl::StringButtonSDL(new sdl::StringSDL(textPair.second, FONT_BASE, SIZE, BASE_TEXT_COLOR, renderer),
				HOVER_TEXT_COLOR, [&](){ convertImageEvent(textPair.first); }));
		y++;
	}
	pane.addComponent(y, new sdl::StringButtonSDL(
		new sdl::StringSDL("Back", FONT_BASE, SIZE, BASE_TEXT_COLOR, renderer), HOVER_TEXT_COLOR, [&](){ stateManager.switchState(WindowState::EDIT_IMAGE); }));
	onWindowResize();
}

AsciiConvertStateSDL::~AsciiConvertStateSDL()
{
}

void AsciiConvertStateSDL::handleTick(SDL_Event& event)
{
	pane.checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane.tickOnClick(); break;
		case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) stateManager.switchState(WindowState::EDIT_IMAGE); break;
	}
}

void AsciiConvertStateSDL::onWindowResize()
{
	pane.center(winInfo.w, winInfo.h);
	pane.reposeContent();
}

void AsciiConvertStateSDL::onReturn()
{
	onWindowResize();
}

void AsciiConvertStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane.draw(renderer);
}

} /* namespace ConsoleArt */
